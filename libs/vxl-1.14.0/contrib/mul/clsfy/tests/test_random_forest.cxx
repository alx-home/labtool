// This is mul/clsfy/tests/test_random_forest.cxx
#include <testlib/testlib_test.h>
//:
// \file
// \brief Tests the clsfy_binary_threshold_1d class
// \author dac
// Test construction, IO etc

#include <vcl_iostream.h>
#include <vcl_string.h>
#include <vcl_numeric.h>
#include <vcl_algorithm.h>
#include <vnl/vnl_math.h>
#include <vpl/vpl.h> // vpl_unlink()
#include <clsfy/clsfy_random_forest.h>
#include <clsfy/clsfy_random_forest_builder.h>
#include <clsfy/clsfy_binary_threshold_1d_builder.h>
#include <vsl/vsl_binary_loader.h>
#include <vsl/vsl_vector_io.h>
#include <pdf1d/pdf1d_gaussian.h>
#include <pdf1d/pdf1d_sampler.h>
#include <pdf1d/pdf1d_flat.h>
#include <vpdfl/vpdfl_axis_gaussian.h>
#include <vpdfl/vpdfl_axis_gaussian_sampler.h>
#include <mbl/mbl_data_array_wrapper.h>
#include <vimt/vimt_transform_2d.h>
#include <vgl/vgl_point_2d.h>

#ifndef LEAVE_FILES_BEHIND
#define LEAVE_FILES_BEHIND 0
#endif

//: Tests the clsfy_binary_threshold_1d class
void test_random_forest()
{
    vcl_cout << "*******************************************\n"
             << " Testing clsfy_random_forest_builder\n"
             << "*******************************************\n";

    const double varx= 1.0;
    const double vary = 1.0;
    const double varz = 1.0;

    const double mux=0.5;
    const double muy=1.0;
    const double muz=2.0;

    pdf1d_gaussian pdfx(mux,varx);
    pdf1d_gaussian pdfy(muy,vary);
    pdf1d_sampler* pdfx_sampler = 0;
    pdf1d_sampler* pdfy_sampler = 0;

    pdf1d_gaussian pdfz(muz,varz);
    pdf1d_sampler* pdfz_sampler = 0;

    pdf1d_gaussian pdferror(0.0,0.02*0.02);
    pdf1d_sampler* pdferror_sampler = 0;

    pdfx_sampler = pdfx.new_sampler();

    unsigned long ixseed = 12345671;
    pdfx_sampler->reseed(ixseed);

    pdfy_sampler = pdfy.new_sampler();
    unsigned long iyseed = 7653215;
    pdfy_sampler->reseed(iyseed);

    pdfz_sampler = pdfz.new_sampler();
    unsigned long izseed = 56789123;
    pdfy_sampler->reseed(iyseed);

    pdferror_sampler = pdferror.new_sampler();

    unsigned NPOINTS=500;
    vcl_vector<vnl_vector<double > > data(NPOINTS);

    vnl_vector<double> xerr(1);
    vnl_vector<double> yerr(1);
    vcl_vector<unsigned > training_outputs(NPOINTS,0);
    unsigned label=0;
    vnl_vector<double > data1d(NPOINTS);
    for (unsigned i=0; i<NPOINTS;++i)
    {
        data[i].set_size(2);
        pdfx_sampler->get_samples(xerr);
        pdfy_sampler->get_samples(yerr);
        double x=xerr[0];
        double y=yerr[0];
        data[i][0]=x;
        data[i][1]=y;
        if (x<=0.5)
        {
            if (y<0.75) // (y<1000)
                label=0;
            else
                label=1;
        }
        else
        {
            if (y>1.5) // (y>1000)
                label=0;
            else
                label=1;
        }
#if 0
        if (x<mux)
            label=0;
        else
            label=1;
#endif // 0
        training_outputs[i]=label;
        data1d[i]=x;
    }

    mbl_data_array_wrapper<vnl_vector<double> > training_set_inputs(data);

    clsfy_random_forest_builder builder;
    builder.set_ntrees(10);
    clsfy_classifier_base* pBaseClassifier=builder.new_classifier();
    TEST("Type is binary tree",
         pBaseClassifier->is_a()==vcl_string("clsfy_random_forest"), true);
    clsfy_random_forest* pClassifier=dynamic_cast<clsfy_random_forest*>(pBaseClassifier);
    TEST("Can cast to binary tree",pClassifier != 0,true);

    builder.build(*pClassifier,
                  training_set_inputs,
                  1,
                  training_outputs);

    vcl_vector<vnl_vector<double > > testData(NPOINTS);

    vcl_vector<unsigned > test_outputs(NPOINTS,0);
    const double epsilon=0.05;
    vnl_vector<double > error(1);
    unsigned tp=0;
    for (unsigned i=0; i<NPOINTS;++i)
    {
        testData[i].set_size(2);
        pdfx_sampler->get_samples(xerr);
        pdfy_sampler->get_samples(yerr);
        pdferror_sampler->get_samples(error);

        double x=xerr[0];
        double y=yerr[0];
        if (x<=0.5+error[0])
        {
            if (y<0.75-error[0])
                label=0;
            else
                label=1;
        }
        else
        {
            if (y>1.5+error[0])
                label=0;
            else
                label=1;
        }

        test_outputs[i]=label;
        testData[i][0]=x+epsilon;
        testData[i][1]=y-epsilon;
        if (label==1)
            ++tp;
    }

    unsigned tpr=0;
    unsigned tnr=0;
    unsigned fpr=0;
    unsigned fnr=0;
    for (unsigned i=0; i<NPOINTS;++i)
    {
        unsigned label=pClassifier->classify(testData[i]);
        if (test_outputs[i]==0)
        {
            if (label==0)
                ++tnr;
            else
                ++fpr;
        }
        else
        {
            if (label==1)
                ++tpr;
            else
                ++fnr;
        }
    }
    double dN=double(NPOINTS);
    double dtp=double (tp);
    double dtn=double (NPOINTS-tp);
    double testTPR=double (tpr)/dtp;
    double testFPR=double (fpr)/dtn;
    double testTNR=double (tnr)/dtn;
    double testFNR=double (fnr)/dtp;

    vcl_cout<<"True Positive Rate "<<double (tpr)/dtp<<vcl_endl
            <<"False Positive Rate "<<double (fpr)/dtn<<vcl_endl
            <<"True Negative Rate "<<double (tnr)/dtn<<vcl_endl
            <<"False Negative Rate "<<double (fnr)/dtp<<vcl_endl;

    // simple test for binary threshold
    TEST("tpr>0.9", double (tpr)/dtp>0.9, true);
    TEST("fpr<0.1", double (fpr)/dtn<0.1, true);

    vcl_cout<<"======== TESTING I/O ===========\n";

    // add binary loaders
    vsl_add_to_binary_loader(clsfy_random_forest());
    vsl_add_to_binary_loader(clsfy_binary_tree());
    vsl_add_to_binary_loader(clsfy_binary_threshold_1d());

    vcl_string test_path = "test_clsfy_random_forest.bvl.tmp";

    vsl_b_ofstream bfs_out(test_path);
    TEST(("Opened " + test_path + " for writing").c_str(), (!bfs_out ), false);
    vsl_b_write(bfs_out, *pClassifier);
    TEST("Stream OK after writing ", (!bfs_out ), false);
    bfs_out.close();

    clsfy_classifier_base* pBaseClassifierIn=builder.new_classifier();

    vsl_b_ifstream bfs_in(test_path);
    TEST(("Opened " + test_path + " for reading").c_str(), (!bfs_in ), false);
    vsl_b_read(bfs_in, *pBaseClassifierIn);
    TEST("Stream OK after reading ", (!bfs_in ), false);
    bfs_in.close();

    TEST("Type is random forest",
         pBaseClassifierIn->is_a()==vcl_string("clsfy_random_forest"), true);
    clsfy_random_forest* pClassifierIn=dynamic_cast<clsfy_random_forest*>(pBaseClassifierIn);
    TEST("Can cast to random forest",pClassifierIn != 0,true);

    {
        unsigned tp=vcl_count(test_outputs.begin(),test_outputs.end(),1);
        unsigned tpr=0;
        unsigned tnr=0;
        unsigned fpr=0;
        unsigned fnr=0;
        for (unsigned i=0; i<NPOINTS;++i)
        {
            unsigned label=pClassifierIn->classify(testData[i]);
            if (test_outputs[i]==0)
            {
                if (label==0)
                    ++tnr;
                else
                    ++fpr;
            }
            else
            {
                if (label==1)
                    ++tpr;
                else
                    ++fnr;
            }
        }
        double dN=double(NPOINTS);
        double dtp=double (tp);
        double dtn=double (NPOINTS-tp);
        vcl_cout<<"True Positive Rate "<<double (tpr)/dtp<<vcl_endl
                <<"False Positive Rate "<<double (fpr)/dtn<<vcl_endl
                <<"True Negative Rate "<<double (tnr)/dtn<<vcl_endl
                <<"False Negative Rate "<<double (fnr)/dtp<<vcl_endl;

        // simple test for binary threshold
        double tpr_=double (tpr)/dtp;
        double fpr_=double (fpr)/dtn;
        TEST("tpr>0.7", tpr_>0.9, true);
        TEST("fpr<0.3", fpr_<0.1, true);
        TEST("Same TPR as pre-IO ",vcl_fabs(testTPR- tpr_)<1.0E-6,true);
        TEST("Same FPR as pre-IO ",vcl_fabs(testFPR- fpr_)<1.0E-6,true);
    }

    vcl_cout<<"=========swap pos and neg samples round===========\n";

    for (unsigned i=0;i<NPOINTS;++i)
    {
        unsigned label=training_outputs[i];
        if (label==0)
            training_outputs[i]=1;
        else
            training_outputs[i]=0;
        label=test_outputs[i];
        if (label==0)
            test_outputs[i]=1;
        else
            test_outputs[i]=0;
    }
    // Train again with +ve and -ve data swapped round + see if get same error
    clsfy_classifier_base* pBaseClassifier2=builder.new_classifier();
    clsfy_random_forest* pClassifier2=dynamic_cast<clsfy_random_forest*>(pBaseClassifier2);

    builder.build(*pClassifier2,
                  training_set_inputs,
                  1,
                  training_outputs);

    {
        const int NPOINTS=500.0;
        unsigned tp=vcl_count(test_outputs.begin(),test_outputs.end(),1);
        unsigned tpr=0;
        unsigned tnr=0;
        unsigned fpr=0;
        unsigned fnr=0;
        for (unsigned i=0; i<NPOINTS;++i)
        {
            unsigned label=pClassifier2->classify(testData[i]);
            if (test_outputs[i]==0)
            {
                if (label==0)
                    ++tnr;
                else
                    ++fpr;
            }
            else
            {
                if (label==1)
                    ++tpr;
                else
                    ++fnr;
            }
        }
        double dN=double(NPOINTS);
        double dtp=double (tp);
        double dtn=double (NPOINTS-tp);
        vcl_cout<<"True Positive Rate "<<double (tpr)/dtp<<vcl_endl
                <<"False Positive Rate "<<double (fpr)/dtn<<vcl_endl
                <<"True Negative Rate "<<double (tnr)/dtn<<vcl_endl
                <<"False Negative Rate "<<double (fnr)/dtp<<vcl_endl;

        TEST("tpr>0.9", double (tpr)/dtp>0.9, true);
        TEST("fpr<0.1", double (fpr)/dtn<0.1, true);
    }

    {
        vcl_cout<<"TESTING 3D Data..."<<vcl_endl;

        const int NPOINTS=500;
        vcl_vector<vnl_vector<double > > data(NPOINTS);
        vcl_vector<unsigned  > training_outputs(NPOINTS,0);

        //Generate a 3d Gaussian ellipsoidal distribution on the x,y,z axes.
        //Rotate and add an offset
        vpdfl_axis_gaussian pca_model0;
        vpdfl_axis_gaussian pca_model1;
        vnl_vector<double> mean0(3,0.0);
        vnl_vector<double> mean1(3,0.0);
        vnl_vector<double> var0(3);
        vnl_vector<double> var1(3);
        var0[0]=100.0;
        var0[1]=50.0;
        var0[2]=25.0;

        var1[0]=200.0;
        var1[1]=100.0;
        var1[2]=50.0;

        mean1[0]=-40.0;
        mean1[1]=25.0;
        mean1[1]=-10.0;

        pca_model0.set(mean0,var0);
        pca_model1.set(mean1,var1);

        pdf1d_flat flatDist;
        pdf1d_sampler* flat_sampler=0;
        flat_sampler = flatDist.new_sampler();
        vnl_vector<double  > example(3);

        vpdfl_axis_gaussian_sampler sampler0;
        sampler0.set_model(pca_model0);
        vpdfl_axis_gaussian_sampler sampler1;
        sampler1.set_model(pca_model1);

        vimt_transform_2d tx0;
        double theta = vnl_math::pi/6.0; //30 degree rotation
        tx0.set_rigid_body(theta,0.0,0.0);

        vimt_transform_2d tx1;
        theta = -vnl_math::pi/8.0; //-15 degree rotation
        tx1.set_rigid_body(theta,0.0,0.0);

        for (unsigned i=0; i<NPOINTS;++i)
        {
            double x=flat_sampler->sample();
            unsigned label=0;
            if (x<0.65)
            {
                label=0;
                sampler0.sample(example);
                //Rotate the example in the x-y plane to make the PCA extraction less trivial
                vgl_point_2d<double > ptxy(example[0],example[1]);
                vgl_point_2d<double > ptxyRot;
                ptxyRot = tx0(ptxy);
                example[0] = ptxyRot.x();
                example[1] = ptxyRot.y();
            }
            else
            {
                label=1;
                sampler1.sample(example);
                //Rotate the example in the x-y plane to make the PCA extraction less trivial
                vgl_point_2d<double > ptxy(example[0],example[1]);
                vgl_point_2d<double > ptxyRot;
                ptxyRot = tx1(ptxy);
                example[0] = ptxyRot.x();
                example[1] = ptxyRot.y();
            }
            data[i]=example;
            training_outputs[i]=label;
        }

        unsigned ntpos=vcl_count(training_outputs.begin(),training_outputs.end(),
                                 1);
        unsigned ntneg=vcl_count(training_outputs.begin(),training_outputs.end(),
                                 0);
        vcl_cout<<"TRAINING Number of pos ="<<ntpos<<"\t num neg "<<ntneg<<vcl_endl;

        mbl_data_array_wrapper<vnl_vector<double> > training_set_inputs(data);

        clsfy_random_forest_builder builder;
        builder.set_ntrees(500);
//        builder.set_max_depth(20);

        clsfy_classifier_base* pBaseClassifier=builder.new_classifier();
        TEST("Type is random forest",
             pBaseClassifier->is_a()==vcl_string("clsfy_random_forest"), true);
        clsfy_random_forest* pClassifier=dynamic_cast<clsfy_random_forest*>(pBaseClassifier);
        TEST("Can cast to random forest",pClassifier != 0,true);

        builder.build(*pClassifier,
                      training_set_inputs,
                      1,
                      training_outputs);

        vcl_vector<vnl_vector<double > > testData(NPOINTS);

        vcl_vector<unsigned > test_outputs(NPOINTS,0);
//        const double epsilon=0.01;
        const double epsilon=0.0;
        vnl_vector<double > error(1);
        unsigned tp=0;
        for (unsigned i=0; i<NPOINTS;++i)
        {
            double x=flat_sampler->sample();
            unsigned label=0;
            if (x<0.6)
            {
                label=0;
                sampler0.sample(example);
                vgl_point_2d<double > ptxy(example[0],example[1]);
                vgl_point_2d<double > ptxyRot;
                ptxyRot = tx0(ptxy);
                example[0] = ptxyRot.x();
                example[1] = ptxyRot.y();
            }
            else
            {
                label=1;
                sampler1.sample(example);
                vgl_point_2d<double > ptxy(example[0],example[1]);
                vgl_point_2d<double > ptxyRot;
                ptxyRot = tx1(ptxy);
                example[0] = ptxyRot.x();
                example[1] = ptxyRot.y();
            }
            testData[i]=example;
            test_outputs[i]=label;
        }

        tp=vcl_count(test_outputs.begin(),test_outputs.end(),
                     1);
        unsigned tneg=vcl_count(test_outputs.begin(),test_outputs.end(),
                                0);
        vcl_cout<<"TESTING Number of pos ="<<tp<<"\t num neg "<<ntneg<<vcl_endl;

        unsigned tpr=0;
        unsigned tnr=0;
        unsigned fpr=0;
        unsigned fnr=0;

        for (unsigned i=0; i<NPOINTS;++i)
        {
            unsigned label=pClassifier->classify(testData[i]);
            if (test_outputs[i]==0)
            {
                if (label==0)
                    ++tnr;
                else
                    ++fpr;
            }
            else
            {
                if (label==1)
                    ++tpr;
                else
                    ++fnr;
            }
        }
        vcl_cout<<"tp "<<tp<<" tn "<<vcl_endl;
        double dN=double(NPOINTS);
        double dtp=double (tp);
        double dtn=double (NPOINTS-tp);
        double testTPR=double (tpr)/dtp;
        double testFPR=double (fpr)/dtn;
        double testTNR=double (tnr)/dtn;
        double testFNR=double (fnr)/dtp;

        vcl_cout<<"True Positive Rate "<<double (tpr)/dtp<<vcl_endl
                <<"False Positive Rate "<<double (fpr)/dtn<<vcl_endl
                <<"True Negative Rate "<<double (tnr)/dtn<<vcl_endl
                <<"False Negative Rate "<<double (fnr)/dtp<<vcl_endl;

        // simple test for binary threshold
        TEST("tpr>0.9", double (tpr)/dtp>0.9, true);
        TEST("fpr<0.1", double (fpr)/dtn<0.15, true);
    }

    {
        vcl_cout<<"TESTING 5D-Hypersphere Data..."<<vcl_endl;
        const int NPOINTS=2000;
        vcl_vector<vnl_vector<double > > data(NPOINTS);

        pdf1d_gaussian pdferror2(0.0,0.02*0.02);
        pdf1d_sampler* pdferror_sampler2 = pdferror2.new_sampler();;

        vnl_vector<double> xerr(1);
        vnl_vector<double> yerr(1);
        vnl_vector<double> zerr(1);
        vcl_vector<unsigned > training_outputs(NPOINTS,0);
        unsigned label=0;
        vnl_vector<double > data1d(NPOINTS);
        for (unsigned i=0; i<NPOINTS;++i)
        {
            data[i].set_size(5);
            pdfx_sampler->get_samples(xerr);
            pdfy_sampler->get_samples(yerr);
            pdfz_sampler->get_samples(zerr);

            pdferror_sampler->get_samples(error);

            double x=xerr[0];
            double y=yerr[0];
            double z=zerr[0];

            pdfx_sampler->get_samples(xerr);
            pdfy_sampler->get_samples(yerr);

            double xx=xerr[0];
            double yy=yerr[0];

            data[i][0]=x;
            data[i][1]=y;
            data[i][2]=z;
            data[i][3]=xx;
            data[i][4]=yy;

            double rx=x-mux;
            double ry=y-muy;
            double rz=z-muz;
            double rxx=xx-mux;
            double ryy=yy-muy;
            double r=vcl_sqrt(rx*rx+ry*ry+rz*rz+rxx*rxx + ryy*ryy);

            double err= pdferror_sampler2->sample();
            if (r+err<0.9*vcl_sqrt(5.0))
                label=0;
            else
                label=1;
            training_outputs[i]=label;
        }
        mbl_data_array_wrapper<vnl_vector<double> > training_set_inputs(data);

        clsfy_random_forest_builder builder;
        builder.set_ntrees(500);
        clsfy_classifier_base* pBaseClassifier=builder.new_classifier();
        clsfy_random_forest* pClassifier=dynamic_cast<clsfy_random_forest*>(pBaseClassifier);

        vcl_vector<vcl_vector<unsigned> > oobIndices;
        builder.set_oob_indices(&oobIndices);
        double train_error= builder.build(*pClassifier,
                                          training_set_inputs,
                                          1,
                                          training_outputs);
        vcl_cout<<"Training error on hypersphere= "<<train_error<<vcl_endl;

        {
            vcl_vector<vnl_vector<double > > testData(NPOINTS);

            vcl_vector<unsigned > test_outputs(NPOINTS,0);
            const double epsilon=0.02;
            vnl_vector<double > error(1);
            unsigned tp=0;
            for (unsigned i=0; i<NPOINTS;++i)
            {
                testData[i].set_size(5);
                pdfx_sampler->get_samples(xerr);
                pdfy_sampler->get_samples(yerr);
                pdfz_sampler->get_samples(zerr);

                pdferror_sampler->get_samples(error);

                double x=xerr[0];
                double y=yerr[0];
                double z=zerr[0];

                pdfx_sampler->get_samples(xerr);
                pdfy_sampler->get_samples(yerr);

                double xx=xerr[0];
                double yy=yerr[0];

                testData[i][0]=x;
                testData[i][1]=y;
                testData[i][2]=z;
                testData[i][3]=xx;
                testData[i][4]=yy;

                double rx=x-mux;
                double ry=y-muy;
                double rz=z-muz;
                double rxx=xx-mux;
                double ryy=yy-muy;
                double r=vcl_sqrt(rx*rx+ry*ry+rz*rz+rxx*rxx + ryy*ryy);

                double err= pdferror_sampler2->sample();
                if (r+err<0.9*vcl_sqrt(5.0))
                    label=0;
                else
                    label=1;

                test_outputs[i]=label;

                if (label==1)
                    ++tp;
            }

            vcl_cout<<"True positives in test = "<<tp<<vcl_endl;
            unsigned tpr=0;
            unsigned tnr=0;
            unsigned fpr=0;
            unsigned fnr=0;
            for (unsigned i=0; i<NPOINTS;++i)
            {
                unsigned label=pClassifier->classify(testData[i]);
                if (test_outputs[i]==0)
                {
                    if (label==0)
                        ++tnr;
                    else
                        ++fpr;
                }
                else
                {
                    if (label==1)
                        ++tpr;
                    else
                        ++fnr;
                }
            }
            double dN=double(NPOINTS);
            double dtp=double (tp);
            double dtn=double (NPOINTS-tp);
            double testTPR=double (tpr)/dtp;
            double testFPR=double (fpr)/dtn;
            double testTNR=double (tnr)/dtn;
            double testFNR=double (fnr)/dtp;

            vcl_cout<<"True Positive Rate "<<double (tpr)/dtp<<vcl_endl
                    <<"False Positive Rate "<<double (fpr)/dtn<<vcl_endl
                    <<"True Negative Rate "<<double (tnr)/dtn<<vcl_endl
                    <<"False Negative Rate "<<double (fnr)/dtp<<vcl_endl;

            // simple test for binary threshold
            TEST("tpr>0.9", double (tpr)/dtp>0.9, true);
            TEST("fpr<0.1", double (fpr)/dtn<0.15, true);
        }
        {
            //Now repeat with out of bag estimates
            tp=vcl_count(training_outputs.begin(),training_outputs.end(),
                         1);

            vcl_cout<<"True positives in training = "<<tp<<vcl_endl;
            unsigned tpr=0;
            unsigned tnr=0;
            unsigned fpr=0;
            unsigned fnr=0;
            for (unsigned i=0; i<NPOINTS;++i)
            {
                unsigned label=pClassifier->classify_oob(data[i],oobIndices,i);
                if (training_outputs[i]==0)
                {
                    if (label==0)
                        ++tnr;
                    else
                        ++fpr;
                }
                else
                {
                    if (label==1)
                        ++tpr;
                    else
                        ++fnr;
                }
            }
            double dN=double(NPOINTS);
            double dtp=double (tp);
            double dtn=double (NPOINTS-tp);
            double testTPR=double (tpr)/dtp;
            double testFPR=double (fpr)/dtn;
            double testTNR=double (tnr)/dtn;
            double testFNR=double (fnr)/dtp;

            vcl_cout<<"OOB True Positive Rate "<<double (tpr)/dtp<<vcl_endl
                    <<"OOB False Positive Rate "<<double (fpr)/dtn<<vcl_endl
                    <<"OOB True Negative Rate "<<double (tnr)/dtn<<vcl_endl
                    <<"OOB False Negative Rate "<<double (fnr)/dtp<<vcl_endl;

            // simple test for binary threshold
            TEST("tpr>0.9", double (tpr)/dtp>0.9, true);
            TEST("fpr<0.1", double (fpr)/dtn<0.15, true);
        }
    }

#if 0 // 85 lines commented out
    clsfy_classifier_1d* b_thresh_clsfr2=b_thresh_builder.new_classifier();
    double error2= b_thresh_builder.build(*b_thresh_clsfr2,
                                          pos_samples, pos_wts,
                                          neg_samples, neg_wts
                                         );

    b_thresh_clsfr2->print_summary(vcl_cout);

    vcl_cout<<"error2= "<<error2<<vcl_endl;

    TEST_NEAR("error1 ~= error2", error1, error2, 0.001);

    tp=0;
    fp=0;
    for (int i=0; i<n_neg; ++i)
        if ( b_thresh_clsfr2->classify( neg_samples_test[i] ) == 1 ) tp++;

    for (int i=0; i<n_pos; ++i)
        if ( b_thresh_clsfr2->classify( pos_samples_test[i] ) == 1 ) fp++;

    delete b_thresh_clsfr2;

    vcl_cout<<"Applied to test set (with +ve and -ve other way round:\n";
    tpr=(tp*1.0)/n_neg, fpr= (fp*1.0)/n_pos;
    vcl_cout<<"True positives= "<<tpr<<vcl_endl
            <<"False positives= "<<fpr<<vcl_endl;

    te= ((n_neg-tp+fp)*1.0)/(n_pos+n_neg);
    vcl_cout<<"te= "<<te<<vcl_endl;

    // simple test for binary threshold
    TEST( "tpr>0.7", tpr>0.7, true );
    TEST( "fpr<0.3", fpr<0.3, true );

    vcl_cout << "***********************************\n"
             << " Testing clsfy_binary_threshold_1d\n"
             << "***********************************\n";

    // Test various parameter settings
    vnl_vector<double> p(2);
    // i.e. x=>5
    p[0]=1;
    p[1]=5;
    b_thresh_clsfr->set_params(p);
    TEST( "10 > 5", b_thresh_clsfr->classify(10), 1 );
    TEST( "2 < 5", b_thresh_clsfr->classify(2), 0 );

    // i.e. x=<5
    p[0]=-1;
    p[1]=-5;
    b_thresh_clsfr->set_params(p);
    TEST( "10 > 5", b_thresh_clsfr->classify(10), 0 );
    TEST( "2 < 5", b_thresh_clsfr->classify(2), 1 );

    // Test loading clsfy_binary_threshold_1d by base class pointer

    vcl_cout<<"======== TESTING I/O ===========\n";

    // add binary loaders
    vsl_add_to_binary_loader(clsfy_binary_threshold_1d());
    vcl_string test_path = "test_clsfy_simple_adaboost.bvl.tmp";

    vsl_b_ofstream bfs_out(test_path);
    TEST(("Opened " + test_path + " for writing").c_str(), (!bfs_out ), false);
    vsl_b_write(bfs_out, *b_thresh_clsfr);
    bfs_out.close();

    clsfy_classifier_1d* classifier_in = b_thresh_builder.new_classifier();;

    vsl_b_ifstream bfs_in(test_path);
    TEST(("Opened " + test_path + " for reading").c_str(), (!bfs_in ), false);
    vsl_b_read(bfs_in, *classifier_in);

    bfs_in.close();
#if !LEAVE_FILES_BEHIND
    vpl_unlink(test_path.c_str());
#endif

    vcl_cout<<"Saved :\n"
            << *b_thresh_clsfr << vcl_endl
            <<"Loaded:\n"
            << classifier_in << vcl_endl;

    TEST("saved classifier = loaded classifier",
         b_thresh_clsfr ->params(), classifier_in->params());
#endif // 85 lines commented out

    vcl_cout<<"Deleting classifiers"<<vcl_endl;
    delete pClassifier;
    vcl_cout<<"Deleting the second classifer"<<vcl_endl;
    delete pClassifier2;
    vcl_cout<<"have deleted classifiers"<<vcl_endl;

    delete pClassifierIn;
    vsl_delete_all_loaders();
}

TESTMAIN(test_random_forest);
