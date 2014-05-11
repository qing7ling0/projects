#include "NumberLabel.h"


NumberLabel::NumberLabel(void)
	: _texture (nullptr)
	, _number (0)
	, _numWidth (0)
{
}


NumberLabel::~NumberLabel(void)
{
	CC_SAFE_RELEASE(_texture);
}

bool NumberLabel::init(Texture2D *texture, const int number)
{
	if(!Node::init()) return false;

	_texture = texture;
	CC_SAFE_RETAIN(_texture);

	if (_texture)
	{
		_numWidth = _texture->getContentSize().width/10;
		setContentSize(Size(0,_texture->getContentSize().height));
	}

	_node = Layer::create();
	addChild(_node);
	

	setNum(number);

	return true;
}

void NumberLabel::setNum(const int number)
{
	if (_number != number)
	{
		_number = number;
		_node->removeAllChildren();

		int temp = number;
		std::vector<int> digitNumbers;
		while(temp>0)
		{
			digitNumbers.push_back(temp%10);
			temp /= 10;
		}

		setContentSize(Size(_numWidth*digitNumbers.size(), _contentSize.height));
		int dsize=digitNumbers.size();
		for(int i=0; i!=dsize; i++)
		{
			temp = digitNumbers[i];
			auto sp = Sprite::createWithSpriteFrame(SpriteFrame::createWithTexture(_texture, Rect(temp*_numWidth,0, _numWidth, _texture->getContentSize().height)));
			sp->ignoreAnchorPointForPosition(true);
			sp->setPositionX((dsize-i-1)*_numWidth);
			_node->addChild(sp);
		}
	}
}
