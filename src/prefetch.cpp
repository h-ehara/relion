
#include "src/prefetch.h"



void * main_PrefetchSmallFiles(void * data)
{
	glob_t glob_result;
	char gomi[1024*256];
	char *filename=(char*)data;
	
	int error = pthread_detach(pthread_self());
	
	glob(filename, GLOB_TILDE, NULL, &glob_result);
	std::cerr << "main_PrefetchSmallFiles_ehara1 n= " << glob_result.gl_pathc << " " << filename << std::endl;
	
	
#pragma omp parallel for num_threads(8) schedule(static,100)
	for(unsigned long int i = 0; i < glob_result.gl_pathc; ++i)
	{
		FILE *fp=fopen(glob_result.gl_pathv[i],"rb");
		if(fp==NULL)
		{
			std::cerr << "Error opening " << glob_result.gl_pathv[i] << std::endl;
			continue;
		}
		fread(gomi,1024*256,1,fp);
		fclose(fp);
		if(i%2000==0)std::cerr << i <<"/" <<glob_result.gl_pathc  << std::endl;
	}
	
	
	
	globfree(&glob_result);
	
	free(data);
	return EXIT_SUCCESS;
}

void start_PrefetchSmallFiles(const char *filename)
{
    //Create threads
    int result;
	pthread_t thread;
	char *filename2=(char*)malloc(4096);
	strncpy(filename2,filename,3000);
	filename2[3000]=0;
	
	std::cerr << "PrefetchSmallFiles_ehara1  " << filename << std::endl;
	result = pthread_create(&thread, NULL, main_PrefetchSmallFiles, (void*) (filename2));

	if (result != 0)
	{
		std::cerr << "start_PrefetchSmallFiles: can't create threads." << std::endl;
		exit(1);
    }

	
}
