#include "Misc.hpp"

#include "../../Config/Structs.hpp"
#include "../../../Core/Globals.hpp"

void Features::Bunnyhop(CUserCmd* cmd) noexcept
{
	if (!misc.mvmnt.bunnyhop)
		return;

	if (!Globals::localPlayer && !Globals::localPlayer->IsAlive())
		return;

	if (!(Globals::localPlayer->GetFlags() & CEntity::FL_ONGROUND))
		cmd->buttons &= ~CUserCmd::IN_JUMP;
}