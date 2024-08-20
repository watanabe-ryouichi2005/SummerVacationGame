#include "WorldTransform.h"
#include "MyMath.h"
void WorldTransform::UpdetaMatrix() {
	
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	
	TransferMatrix();

}

	

