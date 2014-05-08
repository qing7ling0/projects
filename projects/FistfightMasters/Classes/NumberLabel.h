#pragma once

#include "RPGHead.h"

class NumberLabel : public Node
{
public:
	NumberLabel(void);
	~NumberLabel(void);

	bool init(Texture2D *texture, const int number);

	void setNum(const int number);

	F_CREATE_FUNC_ARGS_2(NumberLabel, Texture2D*, texture, int, number);

private:
	int _number;
	float _numWidth;
	Texture2D *_texture;
	Node *_node;
};

