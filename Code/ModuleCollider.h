#ifndef __ModuleCollider_H__
#define __ModuleCollider_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"

class ModuleCollider : public Module {
public:
	ModuleCollider();
	~ModuleCollider();

	bool Start();
	update_status Update();
	bool CleanUp();
};
#endif // !__MODULECOLLIDER_H__