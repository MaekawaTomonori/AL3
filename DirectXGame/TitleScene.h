#pragma once
class TitleScene{
public:
	void Initialize();
	void Update();
	void Draw();

	bool isFinished() const {
		return finished_;
	}
private:
	bool finished_ = false;
};

