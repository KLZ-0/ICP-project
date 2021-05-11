/**
 * @author Kevin Lackó (xlacko08)
 */
#pragma once

#include <mqtt/iaction_listener.h>

namespace Core
{
	class Client;
	/**
	 * @class ActionListener
	 * @brief used by the client to check if a given mqtt action succeeded
	*/
	class ActionListener : public virtual mqtt::iaction_listener
	{
	public:
		/**
		 * @brief ActionListener Constructor
		 * @param caller	pointer to Core::Client for emitting signals 
		*/
		ActionListener(Client *caller);

	private:
		/**
		 * @brief This method is invoked when an action has completed successfully.
		 * @param asyncActionToken
		 */
		void on_success(const mqtt::token &tok) override;
		/**
		 * @brief This method is invoked when (re)connection fails
		 * @param asyncActionToken
		 */
		void on_failure(const mqtt::token &tok) override;

	private:
		Client *sig_;
	};
} // namespace Core
