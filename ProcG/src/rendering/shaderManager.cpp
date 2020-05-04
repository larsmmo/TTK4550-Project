#include "shaderManager.hpp"
#include "shader.hpp"


ShaderManager::ProgramManager()
{
	createDefaultProgramProcessors();
	createDefaultProgramWriterFactories();
}

//-----------------------------------------------------------------------------
ShaderManager::~ProgramManager()
{
	flushGpuProgramsCache();
	destroyDefaultProgramWriterFactories();
	destroyDefaultProgramProcessors();
	destroyProgramWriters();
}

//-----------------------------------------------------------------------------
void ShaderManager::releasePrograms(const ProgramSet* programSet)
{
	GpuProgramPtr vsProgram(programSet->getGpuProgram(GPT_VERTEX_PROGRAM));
	GpuProgramPtr psProgram(programSet->getGpuProgram(GPT_FRAGMENT_PROGRAM));

	GpuProgramsMapIterator itVsGpuProgram = !vsProgram ? mVertexShaderMap.end() : mVertexShaderMap.find(vsProgram->getName());
	GpuProgramsMapIterator itFsGpuProgram = !psProgram ? mFragmentShaderMap.end() : mFragmentShaderMap.find(psProgram->getName());

	if (itVsGpuProgram != mVertexShaderMap.end())
	{
		if (itVsGpuProgram->second.use_count() == ResourceGroupManager::RESOURCE_SYSTEM_NUM_REFERENCE_COUNTS + 1)
		{
			destroyGpuProgram(itVsGpuProgram->second);
			mVertexShaderMap.erase(itVsGpuProgram);
		}
	}

	if (itFsGpuProgram != mFragmentShaderMap.end())
	{
		if (itFsGpuProgram->second.use_count() == ResourceGroupManager::RESOURCE_SYSTEM_NUM_REFERENCE_COUNTS + 1)
		{
			destroyGpuProgram(itFsGpuProgram->second);
			mFragmentShaderMap.erase(itFsGpuProgram);
		}
	}
}
//-----------------------------------------------------------------------------
void ShaderManager::flushGpuProgramsCache()
{
	flushGpuProgramsCache(mVertexShaderMap);
	flushGpuProgramsCache(mFragmentShaderMap);
}

size_t ShaderManager::getShaderCount(GpuProgramType type) const
{
	switch (type)
	{
	case GPT_VERTEX_PROGRAM:
		return mVertexShaderMap.size();
	case GPT_FRAGMENT_PROGRAM:
		return mFragmentShaderMap.size();
	default:
		return 0;
	}
}
//-----------------------------------------------------------------------------
void ShaderManager::flushGpuProgramsCache(GpuProgramsMap& gpuProgramsMap)
{
	while (gpuProgramsMap.size() > 0)
	{
		GpuProgramsMapIterator it = gpuProgramsMap.begin();

		destroyGpuProgram(it->second);
		gpuProgramsMap.erase(it);
	}
}

//-----------------------------------------------------------------------------
void ShaderManager::createDefaultProgramWriterFactories()
{
	// Add standard shader writer factories 

	mProgramWriterFactories.push_back(ShaderProgramWriterGLSLESFactory());

	for (unsigned int i = 0; i < mProgramWriterFactories.size(); ++i)
	{
		ProgramWriterManager::getSingletonPtr()->addFactory(mProgramWriterFactories[i]);
	}
}

//-----------------------------------------------------------------------------
void ShaderManager::destroyDefaultProgramWriterFactories()
{
	for (unsigned int i = 0; i<mProgramWriterFactories.size(); i++)
	{
		ProgramWriterManager::getSingletonPtr()->removeFactory(mProgramWriterFactories[i]);
		//mProgramWriterFactories[i];
	}
	mProgramWriterFactories.clear();
}

//-----------------------------------------------------------------------------
void ShaderManager::createDefaultProgramProcessors()
{
	// Add standard shader processors

	mDefaultProgramProcessors.push_back(GLSLProgramProcessor);

	for (unsigned int i = 0; i < mDefaultProgramProcessors.size(); ++i)
	{
		addProgramProcessor(mDefaultProgramProcessors[i]);
	}
}

//-----------------------------------------------------------------------------
void ShaderManager::destroyDefaultProgramProcessors()
{
	for (unsigned int i = 0; i < mDefaultProgramProcessors.size(); ++i)
	{
		removeProgramProcessor(mDefaultProgramProcessors[i]);
		//mDefaultProgramProcessors[i];
	}
	mDefaultProgramProcessors.clear();
}

//-----------------------------------------------------------------------------
void ShaderManager::destroyProgramWriters()
{
	ProgramWriterIterator it = mProgramWritersMap.begin();
	ProgramWriterIterator itEnd = mProgramWritersMap.end();

	for (; it != itEnd; ++it)
	{
		if (it->second != NULL)
		{
			// it->second;
			it->second = NULL;
		}
	}
	mProgramWritersMap.clear();
}

