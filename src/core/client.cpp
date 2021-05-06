/**
 * @author Kevin Lackó (xlacko08)
 */

#include "client.hpp"

namespace Core
{
	Client::Client(const std::string &clientId)
		: client_(kServerUri.data(), clientId) {
		connOpts_.set_clean_session(false);
		connOpts_.set_keep_alive_interval(20);
	}
} // namespace Core
