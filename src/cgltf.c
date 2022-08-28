//#pragma warning(disable : 26451)
//#define _CRT_SECURE_NO_WARNINGS
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>
#include <SL.h>

int cgltf_loadAttribute(slGltfAttribute* attr, cgltf_accessor* acc);

int cgltf_load(slMesh* mesh, char* path)
{
	cgltf_options options;
	memset(&options, 0, sizeof(cgltf_options));
	cgltf_data* data = NULL;
	cgltf_result result = cgltf_parse_file(&options, path, &data);
	if (result != cgltf_result_success)
	{
		printf("Could not load: %s\n", path);
		return 1;
	}
	
	result = cgltf_load_buffers(&options, data, path);
	if (result != cgltf_result_success)
	{
		cgltf_free(data);
		printf("Could not load: %s\n", path);
		return 1;
	}
	result = cgltf_validate(data);
	if (result != cgltf_result_success)
	{
		cgltf_free(data);
		printf("Invalid file: %s\n", path);
		return 1;
	}
	else
	{
		// get the image for texture
		slString_set(&mesh->image, data->images->uri);
		
		for(int i=0; i<data->meshes_count; i++)
		{
			cgltf_mesh* meshh = &data->meshes[i];
			for(int j=0; j<meshh->primitives_count; j++)
			{
				cgltf_primitive* prim = &meshh->primitives[j];
				for(int k=0; k<prim->attributes_count; k++)
				{
					cgltf_attribute* attr = &prim->attributes[k];
					cgltf_accessor* acc = attr->data;
					int numCmp = cgltf_num_components(acc->type);
					printf("* type: %d | name: %s | stride: %ld | acc offset : %ld | BVoffset: %ld | numComponent: %d\n___\n",
					 attr->type, 
					 attr->name, 
					 acc->stride, 
					 acc->offset, 
					 acc->buffer_view->offset, 
					 numCmp);
					 
					 if(attr->type == 1)
					 {
					 	cgltf_loadAttribute(mesh->pos, acc);
					 }
					 else if(attr->type == 2)
					 {
					 	cgltf_loadAttribute(mesh->norm, acc);
					 }
					 else if(attr->type == 4)
					 {
					 	cgltf_loadAttribute(mesh->uv, acc);
					 }
				}
				cgltf_accessor* acc = prim->indices;
				mesh->ind->count = acc->count;
				mesh->ind->data = malloc(acc->count * sizeof(unsigned int));
				for(unsigned int u=0; u<acc->count; u++)
				{
					cgltf_accessor_read_uint(acc, u, mesh->ind->data + u, sizeof(unsigned int));
				}
			}
		}
	}
	
	// free cgltf
	if (data == 0)
	{
		printf("WARNING: Can't free null data\n");
	}
	else
	{
		cgltf_free(data);
	}
	return 0;
}

int cgltf_loadAttribute(slGltfAttribute* attr, cgltf_accessor* acc)
{
	attr->numCmp = cgltf_num_components(acc->type);
	attr->count = acc->count;
	attr->stride = acc->stride;
	attr->offset = acc->offset + acc->buffer_view->offset;
	attr->data = malloc(acc->count * acc->stride);
	cgltf_accessor_unpack_floats(acc, attr->data, attr->numCmp * acc->count);
	
	return 0;
}
