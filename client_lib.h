#ifndef CLIENT_LIB_H_
#define CLIENT_LIB_H_

#include <boost/asio.hpp>

#include "visibility.h"

namespace MumbleClient {

class MumbleClient;

class DLL_PUBLIC MumbleClientLib {
  public:
	static MumbleClientLib* instance();
	MumbleClient* NewClient();
	void Run();
	void Shutdown();

  private:
	DLL_LOCAL MumbleClientLib();
	DLL_LOCAL ~MumbleClientLib();

	DLL_LOCAL static MumbleClientLib* instance_;
	boost::asio::io_service io_service_;

	MumbleClientLib(const MumbleClientLib&);
	void operator=(const MumbleClientLib&);
};

}  // end namespace MumbleClient

#endif  // CLIENT_LIB_H_
