//: \file
//  \brief Perform binary erosion on images
//  \author Tim Cootes

#include <vil2/algo/vil2_binary_erode.h>
#include <vil2/vil2_fill.h>

//: Erodes src_image to produce dest_image (assumed single plane)
void vil2_binary_erode(const vil2_image_view<vxl_byte>& src_image,
                        vil2_image_view<vxl_byte>& dest_image,
                        const vil2_structuring_element& element)
{
  assert(src_image.nplanes()==1);
  unsigned ni = src_image.ni();
  unsigned nj = src_image.nj();
  dest_image.resize(ni,nj,1);

  int s_istep = src_image.istep(),  s_jstep = src_image.jstep();
  int d_istep = dest_image.istep(), d_jstep = dest_image.jstep();

  const vxl_byte* src_row0 = src_image.top_left_ptr();
  vxl_byte* dest_row0 = dest_image.top_left_ptr();

  vcl_vector<int> offset;
  vil2_compute_offsets(offset,element,s_istep,s_jstep);

  // Define box in which all element will be valid
  int ilo = -element.min_i();
  int ihi = ni-1-element.max_i();
  int jlo = -element.min_j();
  int jhi = nj-1-element.max_j();

  // Deal with left edge
  for (unsigned i=0;i<ilo;++i)    vil2_fill_col(dest_image,i,vxl_byte(0));
  // Deal with right edge
  for (unsigned i=ihi+1;i<ni;++i) vil2_fill_col(dest_image,i,vxl_byte(0));
  // Deal with bottom edge
  for (unsigned j=0;j<jlo;++j)    vil2_fill_row(dest_image,j,vxl_byte(0));
  // Deal with top edge
  for (unsigned j=jhi+1;j<nj;++j) vil2_fill_row(dest_image,j,vxl_byte(0));

  for (int j=jlo;j<=jhi;++j)
  {
    const vxl_byte* src_p = src_row0 + j*s_jstep + ilo*s_istep;
    vxl_byte* dest_p = dest_row0 + j*d_jstep + ilo * d_istep;

    for (int i=ilo;i<=ihi;++i,src_p+=s_istep,dest_p+=d_istep)
	{
	  if (vil2_binary_erode(src_p,&offset[0],offset.size()))
	    *dest_p=1;
      else
	    *dest_p=0;
    }
  }

}
