// This is brl/bbas/imesh/algo/imesh_project.h
#ifndef imesh_project_h_
#define imesh_project_h_
//:
// \file
// \brief Functions to project a mesh into an image
// \author Matt Leotta (mleotta@lems.brown.edu)
// \date Nov. 8, 2005
//
// \verbatim
//  Modifications
//   <none yet>
// \endverbatim

#include <imesh/imesh_mesh.h>
#include <vpgl/vpgl_proj_camera.h>
#include <vpgl/vpgl_perspective_camera.h>
#include <vpgl/vpgl_lens_distortion.h>
#include <vil/vil_image_view.h>
#include <vgl/vgl_box_2d.h>

//: project the 3D vertices into 2D using the camera
void imesh_project_verts(const vcl_vector<vgl_point_3d<double> >& verts3d,
                         const vpgl_proj_camera<double>& camera,
                         vcl_vector<vgl_point_2d<double> >& verts2d);

//: project the 3D vertices into 2D using the camera
void imesh_project_verts(const imesh_vertex_array<3>& verts3d,
                         const vpgl_proj_camera<double>& camera,
                         vcl_vector<vgl_point_2d<double> >& verts2d);

//: project the 3D vertices into 2D vertices and depths using the camera
void imesh_project_verts(const vcl_vector<vgl_point_3d<double> >& verts3d,
                         const vpgl_proj_camera<double>& camera,
                         vcl_vector<vgl_point_2d<double> >& verts2d,
                         vcl_vector<double>& depths);

//: project the 3D mesh vertices into 2D vertices and depths using the camera
void imesh_project_verts(const imesh_vertex_array<3>& verts3d,
                         const vpgl_proj_camera<double>& camera,
                         vcl_vector<vgl_point_2d<double> >& verts2d,
                         vcl_vector<double>& depths);

//: distort the 2D vertices using the lens
void imesh_distort_verts(const vcl_vector<vgl_point_2d<double> >& in_verts,
                         const vpgl_lens_distortion<double>& lens,
                         vcl_vector<vgl_point_2d<double> >& out_verts);

//: project the mesh onto the image plane using the camera and lens distortion
//  Set each pixel of the image to true if the mesh projects onto it
void imesh_project(const imesh_mesh& mesh,
                   const vpgl_proj_camera<double>& camera,
                   const vpgl_lens_distortion<double>& lens,
                   vil_image_view<bool>& image);

//: project the front-facing triangles of the mesh onto the image plane
//  Using the camera and lens distortion
//  Set each pixel of the image to true if the mesh projects onto it
//  The optional \p bbox returns a 2D bounding box for the projection in the image
void imesh_project(const imesh_mesh& mesh,
                   const vcl_vector<vgl_vector_3d<double> >& normals,
                   const vpgl_proj_camera<double>& camera,
                   const vpgl_lens_distortion<double>& lens,
                   vil_image_view<bool>& image,
                   vgl_box_2d<unsigned int>* bbox = 0);

//: project the mesh onto the image plane using the camera
//  Set each pixel of the image to true if the mesh projects onto it
void imesh_project(const imesh_mesh& mesh,
                   const vpgl_proj_camera<double>& camera,
                   vil_image_view<bool>& image);

//: project the mesh onto the image plane using the camera
//  Set each pixel of the image to the depth to the mesh
void imesh_project_depth(const imesh_mesh& mesh,
                         const vpgl_proj_camera<double>& camera,
                         vil_image_view<double>& image);

//: Render a triangle defined by its vertices
void imesh_render_triangle_interp(const vgl_point_2d<double>& v1,
                                  const vgl_point_2d<double>& v2,
                                  const vgl_point_2d<double>& v3,
                                  const double& i1, const double& i2, const double& i3,
                                  vil_image_view<double>& image);

//: Render the faces of the mesh into the image by interpolating the values at the vertices
//  The minimum value is kept at each pixel (as in computing a depth map)
void imesh_render_triangles_interp(const imesh_regular_face_array<3>& tris,
                                   const vcl_vector<vgl_point_2d<double> >& img_verts,
                                   const vcl_vector<double>& vals,
                                   vil_image_view<double>& image);

//: Triangulates the faces and then calls imesh_render_triangles_interp
void imesh_render_faces_interp(const imesh_mesh& mesh,
                               const vcl_vector<vgl_point_2d<double> >& img_verts,
                               const vcl_vector<double>& vals,
                               vil_image_view<double>& image);

//: Compute the bounds of the projection of a set of image points
//  The returned bounds are the intersection of the input bounds
//  and the bounding box of the points
void imesh_projection_bounds(const vcl_vector<vgl_point_2d<double> >& img_pts,
                             vgl_box_2d<unsigned int>& bbox);

//: back project an image point onto the mesh using the camera
//  Returns the index of the itersected triangle, or -1 for no intersection
int imesh_project_onto_mesh(const imesh_mesh& mesh,
                            const vcl_vector<vgl_vector_3d<double> >& normals,
                            const vcl_vector<vgl_point_2d<double> >& verts2d,
                            const vpgl_perspective_camera<double>& camera,
                            const vgl_point_2d<double>& pt_2d,
                            vgl_point_3d<double>& pt_3d);

//: project a texture point onto a mesh face index with barycentric coordinates
//  Returns the index of the itersected triangle, or -1 for no intersection
int imesh_project_texture_to_barycentric(const imesh_mesh& mesh,
                                         const vgl_point_2d<double>& pt_2d,
                                         vgl_point_2d<double>& pt_uv);

//: project a texture polygon into barycentric coordinates
//  \returns true if the polygon is not clipped by the mesh texture
//  \returns the vector of barycentric points by reference
//  \returns a vector of coded half edge indices
//  the half edge indices are scaled by a factor of 4
//  the last two bits indicate the intersection type:
//  - 0 for face
//  - 1 for edge
//  - 2 for vertex
//  barycentric coordinate refer to the adjacent triangle
//  \returns a mapping from each original point into barycentric points.
//  if an original point is not mapped the value is -1
bool imesh_project_texture_to_barycentric(const imesh_mesh& mesh,
                                          const vcl_vector<vgl_point_2d<double> >& pts_2d,
                                          vcl_vector<vgl_point_2d<double> >& pts_uv,
                                          vcl_vector<unsigned long>& idxs,
                                          vcl_vector<int>& map_back);

//: compute the matrix that maps texture points to 3-d for a given triangle index
// $(x,y,1)$ maps into 3-d $(x,y,z)$
vnl_matrix_fixed<double,3,3>
imesh_project_texture_to_3d_map(const imesh_mesh& mesh, unsigned int tidx);

//: project barycentric coordinates with an index to texture space
//  \param idx is the face index
vgl_point_2d<double>
imesh_project_barycentric_to_texture(const imesh_mesh& mesh,
                                     const vgl_point_2d<double>& pt_uv,
                                     unsigned int idx);

//: project barycentric coordinates with an index the mesh surface (3D)
//  \param idx is the face index
vgl_point_3d<double>
imesh_project_barycentric_to_mesh(const imesh_mesh& mesh,
                                  const vgl_point_2d<double>& pt_uv,
                                  unsigned int idx);

//: back project image points onto the mesh using the camera
//  Returns a vector of all valid 3d points and indices to corresponding 2d points
void imesh_project_onto_mesh(const imesh_mesh& mesh,
                             const vcl_vector<vgl_vector_3d<double> >& normals,
                             const vpgl_perspective_camera<double>& camera,
                             const vcl_vector< vgl_point_2d<double> >& pts_2d,
                             vcl_vector<unsigned int >& idx_2d,
                             vcl_vector<vgl_point_3d<double> >& pts_3d);

//: back project an image point onto the mesh using the camera
//  The resulting point is in barycentric coordinates for the returned triangle
//  Returns the index of the itersected triangle, or -1 for no intersection
int imesh_project_onto_mesh_barycentric(const imesh_mesh& mesh,
                                        const vcl_vector<vgl_vector_3d<double> >& normals,
                                        const vcl_vector<vgl_point_2d<double> >& verts2d,
                                        const vpgl_perspective_camera<double>& camera,
                                        const vgl_point_2d<double>& pt_img,
                                        vgl_point_2d<double>& pt_bary);

//: back project an image point onto the mesh using the camera
//  Then project from the mesh into normalized texture coordinate (UV)
//  Assumes the mesh has both normals and texture coordinates
//  Returns the index of the itersected triangle, or -1 for no intersection
int imesh_project_onto_mesh_texture(const imesh_mesh& mesh,
                                    const vcl_vector<vgl_point_2d<double> >& verts2d,
                                    const vpgl_perspective_camera<double>& camera,
                                    const vgl_point_2d<double>& pt_img,
                                    vgl_point_2d<double>& pt_uv);

#endif // imesh_project_h_
