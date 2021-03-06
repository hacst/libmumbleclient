#include "client_lib.h"

#include <iostream>

#include "client.h"
#include "settings.h"

namespace MumbleClient {

///////////////////////////////////////////////////////////////////////////////

// static
MumbleClientLib* MumbleClientLib::instance_ = NULL;

///////////////////////////////////////////////////////////////////////////////
// MumbleClientLib, private:

MumbleClientLib::MumbleClientLib() {
}

MumbleClientLib::~MumbleClientLib() {
	delete instance_;
}

///////////////////////////////////////////////////////////////////////////////
// MumbleClientLib, public:

MumbleClientLib* MumbleClientLib::instance() {
	if (instance_ == NULL) {
		instance_ = new MumbleClientLib();
		return instance_;
	}

	return instance_;
}

MumbleClient* MumbleClientLib::NewClient() {
	return new MumbleClient(&io_service_);
}

void MumbleClientLib::Run() {
	io_service_.run();
}

void MumbleClientLib::Shutdown() {
	::google::protobuf::ShutdownProtobufLibrary();
}

}  // end namespace MumbleClient
