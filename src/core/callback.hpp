/**
 * @author Kevin Lackó (xlacko08)
 */
#pragma once

#include <mqtt/callback.h>
#include <string>

namespace Core
{
	class Callback : public virtual mqtt::callback, public virtual mqtt::iaction_listener
	{
	public:
		Callback() = delete;
		Callback(mqtt::async_client &client);
		/**
		 * This method is called when the client is connected. 
		 * Note that, in response to an initial connect(), the token from the 
		 * connect call is also signaled with an on_success(). That occurs just 
		 * before this is called. 
		 */
		virtual void connected(const std::string &cause) override;
		/**
		 * This method is called when the connection to the server is lost.
		*/
		virtual void connection_lost(const std::string &cause) override;
		/**
		 * This method is called when a message arrives from the server.
		 */
		virtual void message_arrived(mqtt::const_message_ptr msg) override;
		/**
		 * Called when delivery for a message has been completed, and all
		 * acknowledgments have been received.
		 */
		virtual void delivery_complete(mqtt::delivery_token_ptr tok) override;

		virtual ~Callback() {}

		private:
		/**
		 * This method is invoked when (re)connection fails
		 * @param asyncActionToken
		 */
		virtual void on_failure(const mqtt::token &asyncActionToken) override;
		/**
		 * This method is invoked when an action has completed successfully.
		 * @param asyncActionToken
		 */
		virtual void on_success(const mqtt::token &asyncActionToken) override;

	private:
		static constexpr int kQos = 0;
		static constexpr int kRetryLimit = 5;
		int nRetry_ = 0;
		mqtt::async_client &client_;
	};
} // namespace Core
