


#include "ShaderManager.h"

const string_t ShaderManager::TAG="ShaderManager";

bool ShaderManager::loadShaderProgram(std::string vert,std::string frag){
	TextData& text=loadedTextData[vert+frag];
	GLubyte *vertRawdata,*fragRawdata;
	int vertLength,fragLength;
	resource_t vertRes,fragRes;

	vertRes=gdt_resource_load(&vert[0]);
	vertLength=gdt_resource_length(vertRes);
	vertRawdata =(GLubyte*) gdt_resource_bytes (vertRes);
	text.vertData.append((char*)vertRawdata,vertLength);
	text.vertLength=vertLength;

	fragRes=gdt_resource_load(&frag[0]);
	fragLength=gdt_resource_length(fragRes);
	fragRawdata=(GLubyte*)gdt_resource_bytes(fragRes);
	text.fragData.append((char*)fragRawdata,fragLength);
	text.fragLength=fragLength;

	//gdt_log(LOG_NORMAL, TAG, "test: %s\n%s",&text.vertData[0],&text.fragData[0]);

	gdt_resource_unload(vertRes);
	gdt_resource_unload(fragRes);

	return true;
}
