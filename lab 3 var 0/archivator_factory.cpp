#include "archivator_factory.h"
#include "archive.h"

unique_ptr<IArhivator> ArchivatorFactory::Get(ArchivatorType type)
{
	switch (type)
	{
		case ArchivatorType::LZW : return make_unique<LZWArchivator>();
		case ArchivatorType::RLE : return make_unique<RLEArchivator>();
	}
	return nullptr;
}