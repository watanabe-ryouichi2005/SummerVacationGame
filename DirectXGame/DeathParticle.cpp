
#define NONIMAX

#include<cassert>
#include"DeathParticle.h"
#include"MyMath.h"

void DeathParticle::Init(ViewProjection* viewprojection, Vector3 position) {
	//ワールド変換の初期化
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	viewProjection_ = viewprojection;
	model_=Model::CreateFromOBJ("deathParticle", true);

}
void DeathParticle::Update() {
	counter_ += 1.0f/60.0f;
	if (counter_ >= kDuration) {
		counter_=kDuration;
		isFinished_ = true;
	}
	for (uint32_t i = 0; i < worldTransforms_.size(); ++i) {
		Vector3 velosity = {kSpeed,0,0};
		float angle = kAngleunit*i;
	Matrix4x4 matixRotation = MakeRotateZMatrix(angle);
	velosity = Transform(velosity,matixRotation);
	worldTransforms_[i].translation_+=velosity;

	}
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdetaMatrix();
	}
	if (isFinished_) {
		return;
	}
}
void DeathParticle::Draw() {
	if (isFinished_) {
		return ;
	}
	for (auto& worldTransform : worldTransforms_) {

		model_->Draw(worldTransform,*viewProjection_);
	}
}
