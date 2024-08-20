#define NOMINMAX
#include<cmath>
#include<numbers>
#include"TitleScene.h"
#include"DirectXCommon.h"
#include"Input.h"
TitleScene::~TitleScene(){delete modelPlayer_,delete modelTitle_;}
void TitleScene::Init()
{
modelTitle_ = Model::CreateFromOBJ("TitleFont",true);
modelPlayer_ = Model::CreateFromOBJ("player");
viewProjection_.Initialize();
const float kPlayerTitle = 2.0f;
worldTransformTitle_.Initialize();
worldTransformTitle_.scale_= {kPlayerTitle,kPlayerTitle,kPlayerTitle};
worldTransformTitle_.rotation_.y = -0.62f * std::numbers::pi_v<float>;
const float kPlayerScale = 15.0f;
worldTransformPlayer_.Initialize();
worldTransformPlayer_.scale_ = {kPlayerScale,kPlayerScale,kPlayerScale};
worldTransformPlayer_.rotation_.y = -0.95f * std::numbers::pi_v<float>;
worldTransformPlayer_.translation_.x= -2.0f;
worldTransformPlayer_.translation_.y= -9.0f;


}
void TitleScene::Update()
{
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}
	counter_ += 1.0f/60.0f;
	counter_ =std::fmod(counter_,kTimeTitleMove);
	float angle = counter_ / kTimeTitleMove*2.0f*std::numbers::pi_v<float>;
	worldTransformTitle_.translation_.y = std::sin(angle)-10.0f;
	viewProjection_.TransferMatrix();
	worldTransformTitle_.UpdetaMatrix();
	worldTransformPlayer_.UpdetaMatrix();

}
void TitleScene::Draw()
{
DirectXCommon* dxCommon_ = DirectXCommon::GetInstance(); 
ID3D12GraphicsCommandList* commondList = dxCommon_ -> GetCommandList();
Model::PreDraw(commondList);
modelTitle_->Draw(worldTransformTitle_,viewProjection_);
modelPlayer_->Draw(worldTransformTitle_,viewProjection_);
Model::PostDraw();
}