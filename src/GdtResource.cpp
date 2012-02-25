/*
 * GdtResource.cpp
 *
 * Copyright (c) 2011 Sebastian Ärleryd
 * CopyRight (c) 2012 Carl Andersson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "GdtResource.h"

/*

void*      gdt_resource_bytes (resource_t resource);
int32_t    gdt_resource_length(resource_t resource);
resource_t gdt_resource_load  (string_t   resourcePath);
void       gdt_resource_unload(resource_t resource);

*/

GdtResource::GdtResource(std::string path) {
	mResource = gdt_resource_load(path.c_str());
}

GdtResource::~GdtResource() {
	if(mResource == NULL)
		return;

	gdt_resource_unload(mResource);
}

bool GdtResource::isValid() {
	return mResource != NULL;
}

int32_t GdtResource::getLength() {
	if(mResource == NULL)
		return -1;

	return gdt_resource_length(mResource);
}

void * GdtResource::getBytes() {
	if(mResource == NULL)
		return NULL;

	return gdt_resource_bytes(mResource);
}
