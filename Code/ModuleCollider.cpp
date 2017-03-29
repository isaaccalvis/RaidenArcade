#include "Globals.h"
#include "Application.h"
#include "ModuleCollider.h"

ModuleCollider::ModuleCollider() {}
ModuleCollider::~ModuleCollider() {}

bool ModuleCollider::Start() {

	return true;
}

update_status ModuleCollider::Update() {

	return UPDATE_CONTINUE;
}

bool ModuleCollider::CleanUp() {

	return true;
}