#include "Globals.h"
#include "Application.h"
#include "ModuleCollider.h"

ModuleCollider::ModuleCollider() {}
ModuleCollider::~ModuleCollider() {}

bool ModuleCollider::Start() {
	bool ret = true;
	return ret;
}

update_status ModuleCollider::Update() {

	return UPDATE_CONTINUE;
}

bool ModuleCollider::CleanUp() {
	bool ret = true;
	return ret;
}