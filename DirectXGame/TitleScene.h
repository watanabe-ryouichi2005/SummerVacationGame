#include"Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"
class TitleScene {
public:
~TitleScene();
void Init();
void Update();
void Draw();
bool IsFinished(){return finished_;};

private:
bool finished_ = false;
static inline const float kTimeTitleMove = 2.0f;
ViewProjection viewProjection_;
WorldTransform worldTransformTitle_;
WorldTransform worldTransformPlayer_;
Model* modelPlayer_ = nullptr;
Model* modelTitle_ = nullptr;
float counter_ = 0.0f;


};