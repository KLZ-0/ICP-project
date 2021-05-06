/**
 * @author Kevin Lackó (xlacko08)
 */
#pragma once

#include <mqtt/iaction_listener.h>

namespace Core
{
	class ActionListener : public virtual mqtt::iaction_listener
	{
		void on_success(const mqtt::token &tok) override;
		void on_failure(const mqtt::token &tok) override;
	}
} // namespace Core
