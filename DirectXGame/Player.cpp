﻿#define NOMINMAX
#include<algorithm>
#include<cassert>
#include<numbers>
#include"MyMath.h"
#include"Vector3.h"
#include"Player.h"
#include"MapChipField.h"
#include"Enemy.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"Easing.h"
#include "DebugText.h"


//uint32_t textureHandle 
void Player::Initialize(ViewProjection* viewProjection,const Vector3 position) {

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	viewProjection_ = viewProjection;
	// 右を向かせる(πとか数値情報が定義されてる)
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	// 引数の内容をメンバ変数に記録
	model_ = Model::CreateFromOBJ("player");//	textureHandle_ = textureHandle;
}


void Player::Update() {

	inputMove();
	//衝突情報を初期化
CollisionMapInfo collisionMapinfo{};
collisionMapinfo.move = velocity_;
collisionMapinfo.landing = false;
collisionMapinfo.hitWall = false;
//マップ衝突チェック
CheckMapCollision(collisionMapinfo);
//移動
 worldTransform_.translation_ += collisionMapinfo.move;

 //天井接触による落下開始
 if (collisionMapinfo.ceiling) {
	 velocity_.y = 0;
 }
 //壁接触による減速
 if (collisionMapinfo.hitWall) {
	 velocity_.x *= (1.0f - kAttenuation);

 }
 
	// 移動入力
	
	 // 着地フラグ
	// landing = false;

	 // 地面との当たり判定
	 // 下降中？
	 //if (velocity_.y < 0) {
		// // Y座標が地面以下になったら着地
		// if (worldTransform_.translation_.y <= 2.0f) {
		//	 landing = true;
		// }
	 //}
	

	//// 移動
	//worldTransform_.translation_.x += velocity_.x;
	//worldTransform_.translation_.y += velocity_.y;
	//worldTransform_.translation_.z += velocity_.z;

	//// 接地判定
	//if (onGround_) {
	//	// ジャンプ開始
	//	if (velocity_.y > 0.0f) {
	//		// 空中状態に移行
	//		onGround_ = false;
	//	}
	//}
	//else {
	//	// 着地
	//	if (landing) {
	//		// めり込み排斥
	//		worldTransform_.translation_.y = 1.0f;
	//		// 摩擦で横方向速度が減衰する
	//		velocity_.x *= (1.0f - kAttenuation);
	//		// 下方向速度をリセット
	//		velocity_.y = 0.0f;
	//		// 接地状態に移行
	//		onGround_ = true;
	//	}
	//}
	//接地判定
	UpdateOnGround(collisionMapinfo);
	//旋回制御	
	// AnimateTurn();

	// 行列計算
	worldTransform_.UpdetaMatrix();
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();


}

void Player::CheckMapCollision(CollisionMapInfo& info) {
	CheckMapCollisionUp(info);
CheckMapCollisionDown(info);
	CheckMapCollisionRight(info);
	CheckMapCollisionLeft(info);
}
void Player::CheckMapCollisionUp(CollisionMapInfo& info) {
	//上昇あり？
	if (info.move.y <=0) {
		return;
	}
	std::array<Vector3,kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); ++i) {
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.move,static_cast<Corner>(i));
	}
	MapChipType mapChipType;
	MapChipType mapChipTypeNext;
	//真上の当たり判定を行う
	bool hit =false;
	//左上点の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex+1);
	if (mapChipType == MapChipType::kBlock&&mapChipTypeNext != MapChipType::kBlock ) {
		hit = true;
		
	}
	//右上点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kRightTop]);
	mapChipType =  mapChipField_->GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex);
	mapChipTypeNext =  mapChipField_->GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex+1);
		
	if (mapChipType == MapChipType::kBlock&&mapChipTypeNext !=MapChipType::kBlock ) {
	hit = true;
		
	}
	//ブロックにヒット
	if (hit) {
		//現在座標が壁の外か判定
		MapChipField::IndexSet indexSetNow;
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3 (0,+kHeight/2.0f,0));
			if (indexSetNow.yindex != indexSet.yindex) {
				//めり込みを排除する方向に移動量を設定する 
				indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.move + Vector3(0,+kHeight/2.0f,0));
				//めり込み先ブロックの範囲矩形
				MapChipField::Rect rect=mapChipField_->GetRectByIndex(indexSet.xindex,indexSet.yindex);
				//移動量Y＝上にいるブロックの下端ープレイヤーY座標ープレイヤーの高さ/２＋ブランク
				info.move.y = std::max(0.0f,rect.bottom-worldTransform_.translation_.y-(kHeight/2.0f+kBlank));
				info.ceiling = true;
			}

		}
		

}
void Player::CheckMapCollisionDown(CollisionMapInfo & info)
{//下降あり？　　
	if (info.move.y >= 0) {
		return ;
	}

	std::array<Vector3,kNumCorner>positionNew;
	for (uint32_t i = 0; i < positionNew.size(); ++i) {
		positionNew[i] =
		 CornerPosition(worldTransform_.translation_+info.move,static_cast<Corner>(i));

	}
	MapChipType mapChipType;
	MapChipType mapChipTypeNext;
	//真下の当たり判定を行う
	bool hit = false;
	//左下点
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftBottom]) ;
	mapChipType = mapChipField_ -> GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex-1);
	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
		hit = true;


	}
	//右下点
	indexSet = mapChipField_-> GetMapChipIndexSetByPosition(positionNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex-1);
	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
		hit = true;
	}
	if (hit) {
		//現在座標が壁の外か判定
		MapChipField::IndexSet indexSetNow;
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(0,kHeight/2.0f,0));
		if (indexSetNow.yindex != indexSet.yindex) {
		//めり込みを排除する方向に移動量を設定する
		indexSet = mapChipField_ ->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.move + Vector3(0,-kHeight/2.0f,0));
		MapChipField::Rect rect = mapChipField_-> GetRectByIndex(indexSet.xindex,indexSet.yindex);
		info.move.y = std::min(0.0f,rect.top - worldTransform_.translation_.y + (kHeight/2.0f+kBlank));
		info.landing = true;

		}

	}
}
void Player::CheckMapCollisionRight(CollisionMapInfo& info) {
	if (info.move.x <= 0) {
		return;
	}
	std::array<Vector3,kNumCorner> positionNew;

	for (uint32_t i = 0; i < positionNew.size(); ++i) {
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.move,static_cast<Corner>(i));
	}
	MapChipType mapChipType;
	MapChipType mapChipTypeNext;
	bool hit = false;
	//右上点の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex-1,indexSet.yindex);
	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
		hit = true;
	}
	//右下点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex-1,indexSet.yindex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex-1,indexSet.yindex);
	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
		hit = true;

	}
	//ブロックにヒット
	if (hit) {
		//現在座標が壁の外か判定
		MapChipField::IndexSet indexSetNow;
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_+Vector3(+kWidth/2.0f,0,0));
		if (indexSetNow.xindex != indexSet.xindex) {
			//めり込みを排除する方向に移動量を設定する
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.move+Vector3(+kWidth/2.0f,0,0)); 
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xindex,indexSet.yindex);
			info.move.x = std::max(0.0f,rect.left-worldTransform_.translation_.x - (kWidth/2.0f + kBlank));
			info.hitWall = true;
		}
	}


}
void Player::CheckMapCollisionLeft(CollisionMapInfo& info) {
	//左移動あり?
	if (info.move.x >= 0) {
		return;
	}
	std::array<Vector3,kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); ++i) {
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.move,static_cast<Corner>(i));
		
	}
		MapChipType mapChipType;
		MapChipType mapChipTypeNext;
		bool hit = false;
		//左上点の判定
		MapChipField::IndexSet indexSet;
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftTop]);
		mapChipType = mapChipField_ -> GetMapChipTypeByIndex(indexSet.xindex ,indexSet.yindex);
		mapChipTypeNext = mapChipField_ -> GetMapChipTypeByIndex(indexSet.xindex + 1,indexSet.yindex);
		
		if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
			hit = true;
		}
		//左下点の判定
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftBottom]);
		mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex);
		mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex+1,indexSet.yindex);
		if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
			hit = true;
		}
		//ブロックにヒット
		if (hit) {
			//現在座標が壁の外か判定
			MapChipField::IndexSet indexSetNow;
			indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(-kWidth/2.0f,0,0));
			if (indexSetNow.xindex != indexSet.xindex) {
				//めり込みを排除する方向に移動量を設定する
				indexSet = mapChipField_ ->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.move + Vector3(-kWidth/2.0f,0,0));
				MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xindex,indexSet.yindex);
				info.move.x = std::min(0.0f,rect.right - worldTransform_.translation_.x + (kWidth/2.0f + kBlank));
				info.hitWall = true;
			}
		}

	

}



void Player::Draw() {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
}
void Player::inputMove() {
	if (onGround_) {
		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_RIGHT) ||
			Input::GetInstance()->PushKey(DIK_LEFT)) {

			// 左右加速
			Vector3 acceleration = {};

			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x += kAcceleration;

				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					// 旋回開始時の角度
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマー
					turnTimer_ = kTimeTurn;
				}
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				// 右移動中の左入力
				if (velocity_.x > 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x -= kAcceleration;

				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					// 旋回開始時の角度

					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマー

					turnTimer_ = kTimeTurn;
				}
			}
			/*velocity_.x += acceleration.x;
			velocity_.y += acceleration.y;
			velocity_.z += acceleration.z;*/
			// 加速/減速
			velocity_ +=acceleration;
			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

			if (acceleration.x >= 0.01f || acceleration.x <= -0.01f) {
				acceleration.x = 0;
			}

			if (turnTimer_ > 0.0f) {
				// タイマーのカウントダウン
				turnTimer_ -= 1.0f / 60.0f;

				// 左右の自キャラ角度テーブル
				float destinationRotationYTable[] = {
					std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> *3.0f / 2.0f };
				// 状態に応じた角度を取得する
				float destinationRotationY =
					destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
				// 自キャラの角度を設定する
				worldTransform_.rotation_.y = Easing::Liner(
					destinationRotationY, turnFirstRotationY_, Easing::EaseInOut(turnTimer_));
			}

		}
 
		else {
	 
			// 非入力時は移動減衰をかける
	
			velocity_.x *= (1.0f - kAttenuation);
		}

		if (Input::GetInstance()->PushKey(DIK_UP)) {
			// ジャンプ初速
						velocity_ += Vector3(0, kJumpAcceleration/60.0f, 0);
			/*velocity_.x += 0;
			velocity_.y += kJumpAcceleration/60.0f;
			velocity_.z += 0;*/
		}

	}
 
	else {
	 // 落下速度
	 		velocity_ += Vector3(0, -kGravityAcceleration/60.0f, 0);
	 /*velocity_.x += 0;
	 velocity_.y += -kGravityAcceleration/60.0f;
	 velocity_.z += 0;*/
	 // 落下速度制限
	 velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

	}
}
Vector3 Player::CornerPosition(const Vector3& center, Corner corner)
{
	Vector3 offsetTable[] = {
		{+kWidth/2.0f,-kHeight/2.0f,0},
		{-kWidth/2.0f,-kHeight/2.0f,0},
		{+kWidth/2.0f,+kHeight/2.0f,0},
		{-kWidth/2.0f,+kHeight/2.0f,0},
	};
	

return center + offsetTable[static_cast<uint32_t>(corner)]; 
}
WorldTransform& Player::GetWorldTransform() {
	return worldTransform_;
}
const Vector3 & Player::GetVerosity()
{
 return velocity_;
}
Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;

}
AABB Player::GetAABB() {
	Vector3 worldPos = GetWorldPosition();
	AABB aabb;
	aabb.min = {worldPos.x - kWidth/2.0f,worldPos.y-kHeight/2.0f,worldPos.z-kWidth/2.0f};
	aabb.max = {worldPos.x + kWidth/2.0f,worldPos.y+kHeight/2.0f,worldPos.z+kWidth/2.0f};
	return aabb;

}
void Player::OnCollision(const Enemy * enemy)
{(void)enemy; 
//velocity_= Vector3(0,kJumpAcceleration/60.0f,0);
IsDead = true;

}
void Player::SetMapChipField(MapChipField *newMapChipField_)
{
	
	 mapChipField_ = newMapChipField_;
}
void Player::UpdateOnGround(const CollisionMapInfo& info) {
	if (onGround_) {
		//ジャンプ開始
		if (velocity_.y > 0.0f) {
			onGround_ = false;
		}
		else {
			std::array<Vector3,kNumCorner>positionNew;
			for (uint32_t i = 0; i < positionNew.size(); ++i) {
				positionNew[i] = CornerPosition(worldTransform_.translation_+info.move,static_cast<Corner>(i));

			}
			bool ground = false;
			MapChipType mapChipType;
			MapChipField::IndexSet indexSet;
			//左下点
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftBottom]+Vector3(0,-kGroundSearchHeight,0));
			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex);
			if (mapChipType == MapChipType::kBlock) {
				ground = true;
			}
			//右下点
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kRightBottom]+Vector3(0,-kGroundSearchHeight,0));
			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xindex,indexSet.yindex);
			if (mapChipType == MapChipType::kBlock) {
				ground = true;
			}
			//落下開始
			if (!ground) {
				DebugText::GetInstance()->ConsolePrintf("jump");
				onGround_ = false;
			}
		}
	}
	else {
		if (info.landing) {
				velocity_.x *= (1.0f-kAttenuationLanding);
				velocity_.y = 0.0f;
				DebugText::GetInstance()->ConsolePrintf("onGround");
				onGround_ = true;
			
		}

	}
}