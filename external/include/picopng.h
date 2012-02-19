#include <vector>

/*
 * File:   picopng.h
 * Author: Calle
 *
 * Created on den 5 februari 2012, 14:37
 */

#ifndef PICOPNG_H
#define	PICOPNG_H
int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);


#endif	/* PICOPNG_H */

