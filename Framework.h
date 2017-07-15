#include "sdk.h"
#include "mouse.h"

class MBaseObject
{
public:
	std::string name, caption;
	Vector2D position, size;
	bool visible = false;
	MBaseObject() {}
	MBaseObject(std::string name, std::string caption, Vector2D pos, Vector2D size)
	{
		this->name = name;
		this->caption = caption;
		this->position = pos;
		this->size = size;
	}
	virtual void InputBox() { }
	virtual void Draw() = 0;
};

class MWindow : public MBaseObject
{
public:
	std::vector<MBaseObject*> Children;
	MWindow(std::string name, Vector2D pos, Vector2D size);
	void AddChildControl(MBaseObject * Child);
	virtual void Draw() override;
};

class MCategory : public MBaseObject
{
public:
	MCategory() {}
	std::vector<MBaseObject*> Children;
	MWindow* parent;
	static MCategory* CurrentCategory;
	bool active = false;
	MCategory(std::string name, Vector2D pos, MWindow * parent);
	void AddChildControl(MBaseObject * Child);
	virtual void Draw() override;
};

class MTab : public MBaseObject
{
public:
	MTab() {}
	int index;
	MCategory* parent;
	static MTab * CurrentTab;
	bool active = false;
	std::vector<MBaseObject*> Children;
	MTab(std::string name, MCategory * parent, int index);
	void AddChildControl(MBaseObject* Child);
	virtual void Draw() override;
	MTab(std::string name, MCategory * parent);
};


class MGroup : public MBaseObject
{
public:
	MGroup() {}
	MCategory* category;
	std::vector<MBaseObject*> Children;
	MGroup::MGroup(MCategory* category, std::string name, Vector2D pos, Vector2D size);
	void AddChildControl(MBaseObject* Child);
	virtual void Draw() override;
};

class MPlayerList : public MBaseObject
{
public:
	MPlayerList() {}
	MCategory* category;
	std::vector<MBaseObject*> Children;
	MPlayerList::MPlayerList(MCategory* category, std::string name, Vector2D pos, Vector2D size);
	virtual void Draw() override;
};

class MCheckbox : public MBaseObject
{
public:
	MCheckbox() {}
	bool* Var;
	MGroup* parent;
	MCheckbox::MCheckbox(MGroup* parent, std::string name, bool* variable, Vector2D pos);
	virtual void Draw() override;

};

class MCheckboxCategory : public MBaseObject
{
public:
	MCheckboxCategory() {}
	bool* Var;
	MCategory* parent;
	MCheckboxCategory::MCheckboxCategory(MCategory* parent, std::string name, bool* variable, Vector2D pos);
	virtual void Draw() override;

};


class MComboCategory : public MBaseObject
{
public:
	MComboCategory() {}
	int* Var;
	bool* IsOpen;
	MCategory* parent;
	std::vector<std::string> elements;
	MComboCategory::MComboCategory(MCategory* parent, std::string name, int* variable, Vector2D pos, std::vector<std::string> elements, bool* fuck);
	virtual void Draw() override;
};



class MCombo : public MBaseObject
{
public:
	MCombo() {}
	int* Var;
	bool* IsOpen;
	MGroup* parent;
	std::vector<std::string> elements;
	MCombo::MCombo(MGroup* parent, std::string name, int* variable, Vector2D pos, std::vector<std::string> elements, bool* fuck);
	virtual void Draw() override;
};


class MComboNoParent : public MBaseObject
{
public:
	MComboNoParent() {}
	int* Var;
	bool* IsOpen;
	MGroup* parent;
	std::vector<std::string> elements;
	MComboNoParent::MComboNoParent(std::string name, int* variable, Vector2D pos, std::vector<std::string> elements, bool* fuck);
	virtual void Draw() override;
};


class MKey : public MBaseObject
{
public:
	MKey() {}
	int* Var;
	MGroup* parent;
	MKey::MKey(MGroup* parent, std::string name, int* variable, Vector2D pos);
	virtual void Draw() override;


};

class MTextBox : public MBaseObject
{
public:
	MTextBox() {}
	char* Var;
	MGroup* parent;
	bool GetPressedKeys(std::vector<ButtonCode_t>& pressedKeys);
	std::string* strp;
	MTextBox::MTextBox(MGroup* parent, std::string* name, Vector2D pos, Vector2D size);
	void HandleKeys(int key);
	virtual void Draw() override;

protected:
	bool s_showCaret = false;
	int TimeMade;
	int s_caret_stamp;
	Vector2D font_size;
private:
	std::vector<ButtonCode_t> lastPressedKeys;

};


class MButton : public MBaseObject
{
public:
	MButton() {}
	MButton::MButton(std::string name, Vector2D pos, Vector2D size);
	virtual void Draw() override;

};

class MButtonGroup : public MBaseObject
{
public:
	MButtonGroup() {}
	MGroup* parent;
	MButtonGroup::MButtonGroup(MGroup* parent, std::string name, Vector2D pos, Vector2D size);
	virtual void Draw() override;

};

class MString : public MBaseObject
{
public:
	MString() {}
	MGroup* parent;
	MString::MString(MGroup* parent, std::string text, Vector2D pos);
	virtual void Draw() override;

};


class MSelector : public MBaseObject
{
public:
	MSelector() {}
	int* Var;
	MGroup* parent;
	std::vector<std::string> elements;
	MSelector::MSelector(MGroup* parent, std::string name, int* variable, Vector2D pos, std::vector<std::string> elements);
	virtual void Draw() override;

};

class MSlider : public MBaseObject
{
public:
	MSlider() {}
	int* Var;
	MGroup* parent;
	int min, max;
	int width;
	MSlider(MGroup * parent, std::string name, int * variable, int min, int max, int width, Vector2D pos);
	virtual void Draw() override;

};

class MSliderFloat : public MBaseObject
{
public:
	MSliderFloat() {}
	float* Var;
	MGroup* parent;
	float min, max;
	float width;
	MSliderFloat(MGroup * parent, std::string name, float * variable, float min, float max, int width, Vector2D pos);
	virtual void Draw() override;

};