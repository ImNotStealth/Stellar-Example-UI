#include "Easing.h"

namespace Stellar {

	Easing::Easing()
		: type(EasingType::LINEAR), linearValue(0.f), duration(0.f), value(0.f), start(0.f), end(0.f), changePerSec(0.f), isIncreasing(false) {}

	Easing::Easing(EasingType _type, float _duration, float _start, float _end)
		: type(_type), linearValue(_start), duration(_duration), value(_start), start(_start), end(_end)
	{
		float difference = (float)fabs((double)(_start - _end));
		changePerSec = difference / _duration;
		isIncreasing = _end > _start;
	}

	void Easing::Update(float _deltaTime)
	{
		if (type == EasingType::LINEAR)
		{
			value = UpdateLinearValue(_deltaTime);
		}
		else
		{
			value = EasingMap(GetEasingValue(EasingMap(UpdateLinearValue(_deltaTime), start, end, 0, 1), type), 0, 1, start, end);
		}
	}

	void Easing::Reset()
	{
		linearValue = start;
		value = start;
	}

	void Easing::ResetAndFlip()
	{
		float temp = start;
		start = end;
		end = temp;
		Reset();
		float difference = (float)fabs((double)(start - end));
		changePerSec = difference / duration;
		isIncreasing = end > start;
	}

	bool Easing::IsFinished() const
	{
		return linearValue == end;
	}

	float Easing::UpdateLinearValue(float _deltaTime)
	{
		if (linearValue == end)
		{
			return end;
		}

		if (isIncreasing)
		{
			if (linearValue >= end)
			{
				linearValue = end;
				return linearValue;
			}
			linearValue += changePerSec * _deltaTime;
			if (linearValue > end)
			{
				linearValue = end;
			}
			return linearValue;
		}
		else
		{
			if (linearValue <= end)
			{
				linearValue = end;
				return linearValue;
			}
			linearValue -= changePerSec * _deltaTime;
			if (linearValue < end)
			{
				linearValue = end;
			}
			return linearValue;
		}
	}

	float Easing::EasingMap(float _value, float _minInput, float _maxInput, float _minMapped, float _maxMapped)
	{
		return (_value - _minInput) / (_maxInput - _minInput) * (_maxMapped - _minMapped) + _minMapped;
	}

	float Easing::GetEasingValue(float _x, EasingType _type)
	{
		if (_x <= 0.f)
		{
			return 0;
		}
		else if (_x >= 1.f)
		{
			return 1.f;
		}

		switch (_type)
		{
		case EasingType::IN_SINE:
			return EaseInSine(_x);
		case EasingType::OUT_SINE:
			return EaseOutSine(_x);
		case EasingType::IN_OUT_SINE:
			return EaseInOutSine(_x);
		case EasingType::IN_CUBIC:
			return EaseInCubic(_x);
		case EasingType::OUT_CUBIC:
			return EaseOutCubic(_x);
		case EasingType::IN_OUT_CUBIC:
			return EaseInOutCubic(_x);
		case EasingType::IN_QUINT:
			return EaseInQuint(_x);
		case EasingType::OUT_QUINT:
			return EaseOutQuint(_x);
		case EasingType::IN_OUT_QUINT:
			return EaseInOutQuint(_x);
		case EasingType::IN_CIRC:
			return EaseInCirc(_x);
		case EasingType::OUT_CIRC:
			return EaseOutCirc(_x);
		case EasingType::IN_OUT_CIRC:
			return EaseInOutCirc(_x);
		case EasingType::IN_ELASTIC:
			return EaseInElastic(_x);
		case EasingType::OUT_ELASTIC:
			return EaseOutElastic(_x);
		case EasingType::IN_OUT_ELASTIC:
			return EaseInOutElastic(_x);
		case EasingType::IN_QUAD:
			return EaseInQuad(_x);
		case EasingType::OUT_QUAD:
			return EaseOutQuad(_x);
		case EasingType::IN_OUT_QUAD:
			return EaseInOutQuad(_x);
		case EasingType::IN_QUART:
			return EaseInQuart(_x);
		case EasingType::OUT_QUART:
			return EaseOutQuart(_x);
		case EasingType::IN_OUT_QUART:
			return EaseInOutQuart(_x);
		case EasingType::IN_EXPO:
			return EaseInExpo(_x);
		case EasingType::OUT_EXPO:
			return EaseOutExpo(_x);
		case EasingType::IN_OUT_EXPO:
			return EaseInOutExpo(_x);
		case EasingType::IN_BACK:
			return EaseInBack(_x);
		case EasingType::OUT_BACK:
			return EaseOutBack(_x);
		case EasingType::IN_OUT_BACK:
			return EaseInOutBack(_x);
		case EasingType::IN_BOUNCE:
			return EaseInBounce(_x);
		case EasingType::OUT_BOUNCE:
			return EaseOutBounce(_x);
		case EasingType::IN_OUT_BOUNCE:
			return EaseInOutBounce(_x);

		case EasingType::LINEAR:
		default:
			return Linear(_x);
		}
	}

	float Easing::Linear(float _x)
	{
		return _x;
	}

	float Easing::EaseInSine(float _x)
	{
		return (float)(1.f - cosf((_x * (float)M_PI) / 2.f));
	}

	float Easing::EaseOutSine(float _x)
	{
		return sinf((_x * (float)M_PI) / 2.f);
	}

	float Easing::EaseInOutSine(float _x)
	{
		return -(cosf((float)M_PI * _x) - 1.f) / 2.f;
	}

	float Easing::EaseInCubic(float _x)
	{
		return _x * _x * _x;
	}

	float Easing::EaseOutCubic(float _x)
	{
		return 1.f - powf(1.f - _x, 3.f);
	}

	float Easing::EaseInOutCubic(float _x)
	{
		return _x < 0.5f ? 4.f * _x * _x * _x : 1.f - powf(-2.f * _x + 2.f, 3.f) / 2.f;
	}

	float Easing::EaseInQuint(float _x)
	{
		return _x * _x * _x * _x * _x;
	}

	float Easing::EaseOutQuint(float _x)
	{
		return 1.f - powf(1.f - _x, 5.f);
	}

	float Easing::EaseInOutQuint(float _x)
	{
		return _x < 0.5f ? 16.f * _x * _x * _x * _x * _x : 1 - powf(-2.f * _x + 2.f, 5.f) / 2.f;
	}

	float Easing::EaseInCirc(float _x)
	{
		return 1.f - sqrtf(1.f - powf(_x, 2.f));
	}

	float Easing::EaseOutCirc(float _x)
	{
		return sqrtf(1.f - powf(_x - 1.f, 2.f));
	}

	float Easing::EaseInOutCirc(float _x)
	{
		return _x < 0.5f
			? (1.f - sqrtf(1.f - powf(2.f * _x, 2.f))) / 2.f
			: (sqrtf(1.f - powf(-2.f * _x + 2.f, 2.f)) + 1.f) / 2.f;
	}

	float Easing::EaseInElastic(float _x)
	{
		float c4 = (2.f * (float)M_PI) / 3.f;

		return _x == 0.f ? 0.f : _x == 1.f ? 1.f
			: -powf(2.f, 10.f * _x - 10.f) * sinf((_x * 10.f - 10.75f) * c4);
	}

	float Easing::EaseOutElastic(float _x)
	{
		float c4 = (2.f * (float)M_PI) / 3.f;

		return _x == 0.f ? 0.f : _x == 1.f ? 1.f
			: powf(2.f, -10.f * _x) * sinf((_x * 10.f - 0.75f) * c4) + 1.f;
	}

	float Easing::EaseInOutElastic(float _x)
	{
		float c5 = (2.f * (float)M_PI) / 4.5f;

		return _x == 0.f ? 0.f : _x == 1.f ? 1.f : _x < 0.5f
			? -(powf(2.f, 20.f * _x - 10.f) * sinf((20.f * _x - 11.125f) * c5)) / 2.f
			: (powf(2.f, -20.f * _x + 10.f) * sinf((20.f * _x - 11.125f) * c5)) / 2.f + 1.f;
	}

	float Easing::EaseInQuad(float _x)
	{
		return _x * _x;
	}

	float Easing::EaseOutQuad(float _x)
	{
		return 1.f - (1.f - _x) * (1.f - _x);
	}

	float Easing::EaseInOutQuad(float _x)
	{
		return _x < 0.5f ? 2.f * _x * _x : 1.f - powf(-2.f * _x + 2.f, 2.f) / 2.f;
	}

	float Easing::EaseInQuart(float _x)
	{
		return _x * _x * _x * _x;
	}

	float Easing::EaseOutQuart(float _x)
	{
		return 1.f - powf(1.f - _x, 4.f);
	}

	float Easing::EaseInOutQuart(float _x)
	{
		return _x < 0.5f ? 8.f * _x * _x * _x * _x : 1.f - powf(-2.f * _x + 2.f, 4.f) / 2.f;
	}

	float Easing::EaseInExpo(float _x)
	{
		return _x == 0.f ? 0.f : powf(2.f, 10.f * _x - 10.f);
	}

	float Easing::EaseOutExpo(float _x)
	{
		return _x == 1.f ? 1.f : 1.f - powf(2.f, -10.f * _x);
	}

	float Easing::EaseInOutExpo(float _x)
	{
		return _x == 0.f ? 0.f : _x == 1.f ? 1.f
			: _x < 0.5f ? powf(2.f, 20.f * _x - 10.f) / 2.f
			: (2.f - powf(2.f, -20.f * _x + 10.f)) / 2.f;
	}

	float Easing::EaseInBack(float _x)
	{
		float c1 = 1.70158f;
		float c3 = c1 + 1.f;

		return c3 * _x * _x * _x - c1 * _x * _x;
	}

	float Easing::EaseOutBack(float _x)
	{
		float c1 = 1.70158f;
		float c3 = c1 + 1.f;

		return 1.f + c3 * powf(_x - 1.f, 3.f) + c1 * powf(_x - 1.f, 2.f);
	}

	float Easing::EaseInOutBack(float _x)
	{
		float c1 = 1.70158f;
		float c2 = c1 * 1.525f;

		return _x < 0.5
			? (powf(2.f * _x, 2.f) * ((c2 + 1.f) * 2.f * _x - c2)) / 2.f
			: (powf(2.f * _x - 2.f, 2.f) * ((c2 + 1.f) * (_x * 2.f - 2.f) + c2) + 2.f) / 2.f;
	}

	float Easing::EaseInBounce(float _x)
	{
		return 1.f - EaseOutBounce(1.f - _x);
	}

	float Easing::EaseOutBounce(float _x)
	{
		float n1 = 7.5625f;
		float d1 = 2.75f;

		if (_x < 1.f / d1)
		{
			return n1 * _x * _x;
		}
		else if (_x < 2.f / d1)
		{
			return n1 * (_x -= 1.5f / d1) * _x + 0.75f;
		}
		else if (_x < 2.5f / d1)
		{
			return n1 * (_x -= 2.25f / d1) * _x + 0.9375f;
		}
		else
		{
			return n1 * (_x -= 2.625f / d1) * _x + 0.984375f;
		}
	}

	float Easing::EaseInOutBounce(float _x)
	{
		return _x < 0.5f ? (1.f - EaseOutBounce(1.f - 2.f * _x)) / 2.f : (1.f + EaseOutBounce(2.f * _x - 1.f)) / 2.f;
	}
}