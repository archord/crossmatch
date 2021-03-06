

#include "anwcs.h"


typedef float number;

/*
 typedef bool (*isbadpix)(const number* img, const number* weightimg, int ix, int iy, void* token)
 badpixfunc_t;
 */

struct coadd_s {
	number* img;
	number* weight;
	int W, H;
	anwcs_t* wcs;

	double (*resample_func)(double px, double py,
							const number* img, const number* weightimg,
							int W, int H,
							double* wt,
							//badpixfunc_t badpix,
							//void* isbadpix_token,
							void* resample_token);
	void* resample_token;
	//resample_t* resample;
};
typedef struct coadd_s coadd_t;

coadd_t* coadd_new(int W, int H);

int coadd_add_image(coadd_t* c, const number* img, const number* weightimg,
					number weight, const anwcs_t* wcs);
//, badpixfunc_t badpix, void* badpix_token);

// divide "img" by "weight"; set img=badpix where weight=0.
void coadd_divide_by_weight(coadd_t* c, number badpix);

void coadd_free(coadd_t* c);

