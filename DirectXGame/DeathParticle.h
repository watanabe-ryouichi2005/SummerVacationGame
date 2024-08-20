#include <array>
#include <numbers>
//#include "ObjectColor.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class DeathParticle{
	public:
void Init(ViewProjection* viewProjection,Vector3 position);
void Update();
void Draw();
bool IsFinished(){return isFinished_;};
private:

static inline const uint32_t kNumParticle = 8;
static inline const float kDuration = 2.0f;
static inline const float kSpeed = 0.05f ;
static inline const float kAngleunit = 2.0f * std::numbers::pi_v<float>/kNumParticle;
Model* model_ = nullptr;
std::array<WorldTransform,kNumParticle> worldTransforms_;
ViewProjection* viewProjection_ = nullptr;
bool isFinished_ = false;
float counter_ = 0.0f;
//ObjectColor objectColor_;
//Vector4 color;

};