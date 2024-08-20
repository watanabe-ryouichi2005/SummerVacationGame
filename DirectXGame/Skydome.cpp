#include "Skydome.h"
#include<cassert>
void Skydome::Initialize(Model* model, uint32_t texturHandle, ViewProjection* viewprojection) {
	assert(model);
	texturHandle_ = texturHandle;
	model_ = model;
	viewProjection_ = viewprojection;
	worldTransform_.Initialize();

}
void Skydome::Update() {

}
void Skydome::Draw() { 
model_->Draw(worldTransform_, *viewProjection_);

}
