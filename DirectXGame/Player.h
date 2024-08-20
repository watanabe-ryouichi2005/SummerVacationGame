#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"AABB.h"
class MapChipField;
class Enemy;
class Player {
public:
	// 左右
	enum class LRDirection {
		kRight,
		kLeft,
	};
	//右下、左下、右上、左上、要素数
	enum Corner {
		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,
		kNumCorner
	};
	//typedef struct AABB {
	//	Vector3 min;
	//	Vector3 max;
	//	/*GetAABBはエネミーとプレイヤーに定義する
	//	IsCollision関数もつくる関数の中身retun(
	//	aabb1.min.x<=aabb2.max.x&&aabb1.max.x<=aabb2.min.x
	//	&&aabb1.min.y<=aabb2/max.y&&aabb1.min.y>=aabb2.max.y
	//	&&aabb1.min.z<=aabb2.max.z&&aabb1.max.z>aabb2.min.z);*/ 
	//    
	//};
	/// <summary>
	/// 初期化
	/// </summary>
		void Initialize(ViewProjection* viewProjection,Vector3 position);
	//void Initialize(const Vector3& position, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	//AABB GetAABB() { WorldPos.x - kWidth / 2, WorldPos.y - kHeight / 2, worldPos.z - kWidth / 2; }

	WorldTransform& GetWorldTransform();
	const Vector3& GetVerosity();
	Vector3 GetWorldPosition();
	AABB GetAABB();
	bool GetIsDead()const {return IsDead;};
	 void OnCollision(const Enemy* enemy);
	 void SetMapChipField(MapChipField* newMapChipField_);

private:
	//キャラクター当たり判定のサイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	static inline const float kBlank  = 0.4f;
	//static inline const float kTimeTurn  = 0.3f;
	static inline const float kAcceleration = 0.01f;
	//static inline const float kJumpAcceleration = 20.0f;
	//static inline const float kGravityAcceleration = 0.98f;
	static inline const float kLimitRunSpeed = 0.5f;
	//static inline const float kLimitFallSpeed = 0.5f;
	static inline const float kAttenuation = 0.05f;
	static inline const float kAttenuationWall = 0.2f;
	static inline const float kAttenuationLanding = 0.0f;
	static inline const float kGroundSearchHeight = 0.06f;

	//マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	Vector3 velocity_ = {};


	LRDirection lrDirection_ = LRDirection::kRight;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;

	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;

	// 接地状態フラグ
	bool onGround_ = true;
	// 着地フラグ
	bool landing = false;
	//死亡フラグ
	bool IsDead = false;
	// 重力加速度（下方向）
	static inline const float kGravityAcceleration = 0.98f;
	// 最大落下速度（下方向）
	static inline const float kLimitFallSpeed = 0.5f;
	// ジャンプ初速（上方向）
	static inline const float kJumpAcceleration = 20.0f;
	//天井衝突フラグ、着地フラグ、壁接触フラグ、Vector3型移動量
	struct CollisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		Vector3  move;
		
	};
	void inputMove();
	void CheckMapCollision(CollisionMapInfo& info);
	void CheckMapCollisionUp(CollisionMapInfo& info);
	void CheckMapCollisionDown(CollisionMapInfo& info);
	void CheckMapCollisionRight(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);
	void UpdateOnGround(const CollisionMapInfo& info);
	void AnimateTurn();
	Vector3 CornerPosition(const Vector3& center,Corner corner);

};