// This is mul/clsfy/clsfy_random_forest.cxx
#include "clsfy_random_forest.h"
//:
// \file
// \brief Random forest classifier
// \author Martin Roberts

#include <vcl_string.h>
#include <vcl_deque.h>
#include <vcl_algorithm.h>
#include <vcl_iterator.h>
#include <vcl_cmath.h>
#include <vcl_cassert.h>
#include <vsl/vsl_binary_io.h>
#include <vsl/vsl_vector_io.h>
#include <vnl/io/vnl_io_vector.h>
#include <mbl/mbl_stl.h>


clsfy_random_forest::clsfy_random_forest()
{
}

//=======================================================================
//: Return the classification of the given probe vector.
unsigned clsfy_random_forest::classify(const vnl_vector<double> &input) const
{
#if 1 //Accumulate probabilities (impure final nodes may not return 0 or 1)
    vcl_vector<double > classProbs(1,0.0);
    class_probabilities(classProbs,input);
    return (classProbs[0]>=0.5) ? 1 : 0;
#else // just accumulate number in each class rather than probs

    vcl_vector<mbl_cloneable_ptr<clsfy_classifier_base> >::const_iterator treeIter=trees_.begin();
    vcl_vector<mbl_cloneable_ptr<clsfy_classifier_base> >::const_iterator treeIterEnd=trees_.end();

    vcl_vector<unsigned > classCount(2,0);

    unsigned i=0;
    while (treeIter != treeIterEnd)
    {
        mbl_cloneable_ptr<clsfy_classifier_base> pTree=*treeIter++;
        unsigned treeClass= pTree->classify(input);

        ++classCount[treeClass];
    }
    if (classCount[0] >= classCount[1])
        return 0;
    else
        return 1;
#endif // 1
}

//=======================================================================
//: Return a probability like value that the input being in each class.
// output(i) i<<nClasses, contains the probability that the input is in class i
void clsfy_random_forest::class_probabilities(vcl_vector<double>& outputs,
                                              vnl_vector<double>const& input) const
{
    outputs.resize(1);

    vcl_vector<mbl_cloneable_ptr<clsfy_classifier_base> >::const_iterator treeIter=trees_.begin();
    vcl_vector<mbl_cloneable_ptr<clsfy_classifier_base> >::const_iterator treeIterEnd=trees_.end();

    vcl_vector<double > classProbs(1,0.0);
    vcl_vector<double > meanProbs(1,0.0);
    unsigned i=0;
    while (treeIter != treeIterEnd)
    {
        const clsfy_classifier_base* pTree=(*treeIter).ptr();
        pTree->class_probabilities(classProbs, input);
        meanProbs[0]+=classProbs[0];
        ++treeIter;
    }
    outputs[0]=meanProbs[0]/double (trees_.size());
}


//=======================================================================
//: This value has properties of a Log likelihood of being in class (binary classifiers only)
// class probability = exp(logL) / (1+exp(logL))
double clsfy_random_forest::log_l(const vnl_vector<double> &input) const
{
    //Retain logistic function relation to prob
    //i.e. invert the above relation
    double epsilon=1.0E-8;
    vcl_vector<double > probs(1,0.5);
    class_probabilities(probs,input);
    double p=probs[0];
    double d=(1.0/p)-1.0;
    double x=1.0;
    if (d>epsilon)
        x=-vcl_log(d);
    else
        x=-vcl_log(epsilon);

    return x;
}

//======================= Out of Bag add-ons ==============================
void clsfy_random_forest::class_probabilities_oob(vcl_vector<double> &outputs,
                                                  const vnl_vector<double> &input,
                                                  const vcl_vector<vcl_vector<unsigned > >& oobIndices,
                                                  unsigned this_index) const
{
    outputs.resize(1);

    vcl_vector<mbl_cloneable_ptr<clsfy_classifier_base> >::const_iterator treeIter=trees_.begin();
    vcl_vector<mbl_cloneable_ptr<clsfy_classifier_base> >::const_iterator treeIterEnd=trees_.end();

    vcl_vector<double > classProbs(1,0.0);
    vcl_vector<double > meanProbs(1,0.0);
    vcl_vector<vcl_vector<unsigned > >::const_iterator oobIndexIter=oobIndices.begin() ;
    unsigned noob=0;
    while (treeIter != treeIterEnd)
    {
        if (vcl_find(oobIndexIter->begin(),oobIndexIter->end(),this_index)==oobIndexIter->end())
        {
            //Not found this_index, so Out of Bag - accumulate this tree's vote
            const clsfy_classifier_base* pTree=(*treeIter).ptr();

            pTree->class_probabilities(classProbs, input);
            meanProbs[0]+=classProbs[0];
            ++noob;
        }
        ++treeIter;
        ++oobIndexIter;
    }
    outputs[0]=meanProbs[0]/double (noob);
}


//: Return the classification of the given probe vector using out of bag trees only.
// See also class_probabilities_oob
unsigned clsfy_random_forest::classify_oob(const vnl_vector<double> &input,
                                           const vcl_vector<vcl_vector<unsigned > >& oobIndices,
                                           unsigned this_index) const
{
    vcl_vector<double > classProbs(1,0.0);
    class_probabilities_oob(classProbs,input,oobIndices,this_index);
    return (classProbs[0]>=0.5) ? 1 : 0;
}


//=======================================================================

vcl_string clsfy_random_forest::is_a() const
{
    return vcl_string("clsfy_random_forest");
}

//=======================================================================

bool clsfy_random_forest::is_class(vcl_string const& s) const
{
    return s == clsfy_random_forest::is_a() || clsfy_classifier_base::is_class(s);
}

//=======================================================================

short clsfy_random_forest::version_no() const
{
    return 1;
}

//=======================================================================

clsfy_classifier_base* clsfy_random_forest::clone() const
{
    return new clsfy_random_forest(*this);
}

//=======================================================================

void clsfy_random_forest::print_summary(vcl_ostream& os) const
{
    os<<"clsfy_random_forest\t has "<<trees_.size()<<" trees"<<vcl_endl;
}

//=======================================================================

void clsfy_random_forest::b_write(vsl_b_ostream& bfs) const
{
    vcl_cout<<"clsfy_random_forest::b_write"<<vcl_endl;
    vsl_b_write(bfs,version_no());
    unsigned n=trees_.size();
    vsl_b_write(bfs,n);
    for (unsigned i=0; i<n;++i)
    {
        trees_[i]->b_write(bfs);
    }
}

//=======================================================================

void clsfy_random_forest::b_read(vsl_b_istream& bfs)
{
    if (!bfs) return;

    prune();
    short version;
    vsl_b_read(bfs,version);
    switch (version)
    {
        case 1:
        {
            unsigned n;
            vsl_b_read(bfs,n);
            vcl_cout<<"Am attemptig to read in "<<n<<"\t trees"<<vcl_endl;
            trees_.reserve(n);
            for (unsigned i=0; i<n;++i)
            {
                vcl_cout<<"reading tree "<<i<<vcl_endl;
                mbl_cloneable_ptr< clsfy_classifier_base> tree(new clsfy_binary_tree);
                trees_.push_back(tree);
                trees_.back()->b_read(bfs);
            }
            break;
        }

        default:
            vcl_cerr << "I/O ERROR: clsfy_random_forest::b_read(vsl_b_istream&)\n"
                     << "           Unknown version number "<< version << '\n';
            bfs.is().clear(vcl_ios::badbit); // Set an unrecoverable IO error on stream
    }
}

clsfy_random_forest::~clsfy_random_forest()
{
    prune();
}

void clsfy_random_forest::prune()
{
    trees_.clear(); //note mbl wrapper destructor deletes the tree pointer!
}

//=======================================================================
//: The dimensionality of input vectors.
unsigned clsfy_random_forest::n_dims() const
{
    if (trees_.empty())
        return 0;
    else
        return trees_.front()->n_dims();
}

clsfy_random_forest& clsfy_random_forest::operator+=(const clsfy_random_forest& forest2)
{
    this->trees_.reserve(this->trees_.size()+forest2.trees_.size());
    this->trees_.insert(this->trees_.end(),
                        forest2.trees_.begin(),forest2.trees_.end());
    return *this;
}


//============ Friend functions for merging stuff ====================

//: Merge the sub-forests in the input filenames into a single larger one
void merge_sub_forests(const vcl_vector<vcl_string>& filenames,
                       clsfy_random_forest& large_forest)
{
    vcl_vector<vcl_string>::const_iterator fileIter=filenames.begin();
    vcl_vector<vcl_string>::const_iterator fileIterEnd=filenames.end();
    while (fileIter != fileIterEnd)
    {
        vsl_b_ifstream bfs_in(*fileIter);
        clsfy_random_forest subForest;
        vsl_b_read(bfs_in, subForest);
        bfs_in.close();
        large_forest.trees_.reserve(large_forest.trees_.size()+subForest.trees_.size());
        large_forest.trees_.insert(large_forest.trees_.end(),
                                   subForest.trees_.begin(),subForest.trees_.end());
        ++fileIter;
    }
}

//: Merge the sub-forests pointed to the input vector a single larger one
void merge_sub_forests(const vcl_vector< clsfy_random_forest*>& sub_forests,
                       clsfy_random_forest& large_forest)
{
    vcl_vector<clsfy_random_forest*>::const_iterator subForestIter=sub_forests.begin();
    vcl_vector<clsfy_random_forest*>::const_iterator subForestIterEnd=sub_forests.end();
    while (subForestIter != subForestIterEnd)
    {
        const clsfy_random_forest& subForest=**subForestIter;
        large_forest.trees_.reserve(large_forest.trees_.size()+subForest.trees_.size());
        large_forest.trees_.insert(large_forest.trees_.end(),
                                   subForest.trees_.begin(),subForest.trees_.end());
        ++subForestIter;
    }
}

//: Merge the two input forests
clsfy_random_forest operator+(const clsfy_random_forest& forest1,
                              const clsfy_random_forest& forest2)
{
    clsfy_random_forest mergedForest=forest1;

    mergedForest.trees_.reserve(forest1.trees_.size()+forest2.trees_.size());
    mergedForest.trees_.insert(mergedForest.trees_.end(),
                               forest2.trees_.begin(),forest2.trees_.end());
    return mergedForest;
}

