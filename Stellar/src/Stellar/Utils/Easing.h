#ifndef STELLAR_EASING_H
#define STELLAR_EASING_H

#include "Stellar/Core/Common.h"

namespace Stellar {

	enum class EasingType
	{
		LINEAR,

		IN_SINE,
		OUT_SINE,
		IN_OUT_SINE,

		IN_CUBIC,
		OUT_CUBIC,
		IN_OUT_CUBIC,

		IN_QUINT,
		OUT_QUINT,
		IN_OUT_QUINT,

		IN_CIRC,
		OUT_CIRC,
		IN_OUT_CIRC,

		IN_ELASTIC,
		OUT_ELASTIC,
		IN_OUT_ELASTIC,

		IN_QUAD,
		OUT_QUAD,
		IN_OUT_QUAD,

		IN_QUART,
		OUT_QUART,
		IN_OUT_QUART,

		IN_EXPO,
		OUT_EXPO,
		IN_OUT_EXPO,

		IN_BACK,
		OUT_BACK,
		IN_OUT_BACK,

		IN_BOUNCE,
		OUT_BOUNCE,
		IN_OUT_BOUNCE,
	};

	class Easing
	{
	public:
		Easing();
		Easing(EasingType _type, float _duration, float _start, float _end);

		void Update(float _deltaTime);
		void Reset();
		void ResetAndFlip();
		bool IsFinished() const;

	public:
		EasingType type;
		float linearValue;
		float value;
		float duration;
		float start;
		float end;
		float changePerSec;
		bool isIncreasing;

	private:
		float UpdateLinearValue(float _deltaTime);
		float EasingMap(float _value, float _minInput, float _maxInput, float _minMapped, float _maxMapped);
		float GetEasingValue(float _x, EasingType _type);

		float Linear(float _x);
		float EaseInSine(float _x);
		float EaseOutSine(float _x);
		float EaseInOutSine(float _x);
		float EaseInCubic(float _x);
		float EaseOutCubic(float _x);
		float EaseInOutCubic(float _x);
		float EaseInQuint(float _x);
		float EaseOutQuint(float _x);
		float EaseInOutQuint(float _x);
		float EaseInCirc(float _x);
		float EaseOutCirc(float _x);
		float EaseInOutCirc(float _x);
		float EaseInElastic(float _x);
		float EaseOutElastic(float _x);
		float EaseInOutElastic(float _x);
		float EaseInQuad(float _x);
		float EaseOutQuad(float _x);
		float EaseInOutQuad(float _x);
		float EaseInQuart(float _x);
		float EaseOutQuart(float _x);
		float EaseInOutQuart(float _x);
		float EaseInExpo(float _x);
		float EaseOutExpo(float _x);
		float EaseInOutExpo(float _x);
		float EaseInBack(float _x);
		float EaseOutBack(float _x);
		float EaseInOutBack(float _x);
		float EaseInBounce(float _x);
		float EaseOutBounce(float _x);
		float EaseInOutBounce(float _x);
	};

}

#endif