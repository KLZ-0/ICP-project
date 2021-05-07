/**
 * @author Kevin Lackó (xlacko08)
 */
#pragma once

#include <mqtt/iaction_listener.h>

namespace Core
{
	class Client;
	class ActionListener : public virtual mqtt::iaction_listener
	{
	public:
		ActionListener(Client *caller);

	private:
		void on_success(const mqtt::token &tok) override;
		void on_failure(const mqtt::token &tok) override;

	private:
		Client *sig_;
	};
} // namespace Core
