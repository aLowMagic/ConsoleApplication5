#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Screen {
public:
	typedef std::string::size_type pos;//使用typedef定义类型别名
	Screen() = default;//生成构造函数
	Screen(pos ht, pos wd, char c) :height(ht), width(wd), contents(ht*wd, c) {}//Screen函数
	char get() const { return contents[cursor]; }//get()构造函数
	inline char get(pos ht, pos wd) const;
	inline Screen &move(pos r, pos c);
	void some_member() const;
	Screen &Set(char);
	Screen &Set(pos, pos, char);
	Screen &display(std::ostream &os) { do_display(os); return *this; }//打印
	const Screen &display(std::ostream &os)const { do_display(os); return *this; }//打印
	friend class Window_mgr;
	pos size() const {}
private:
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
	mutable size_t access_ctr;
	void do_display(std::ostream &os)const { os << contents; };
};
Screen &Screen::move(pos r, pos c) {
	pos row = r*width;
	cursor = row + c;
	return *this;//左值形式返回对象
}
inline Screen &Screen::Set(char c) {
	contents[cursor] = c;
	return *this;
}
inline Screen &Screen::Set(pos r, pos col, char ch) {
	contents[r*width + col] = ch;
	return *this;
}
char Screen::get(pos r, pos c)const {
	pos row = r*width;
	return contents[row + c];
}
void Screen::some_member()const {
	++access_ctr;
}
class Window_mgr {
public:
	using ScreenIndex = std::vector<Screen>::size_type;
	void clear(ScreenIndex);
	ScreenIndex addScreen(const Screen&);
private:
	std::vector<Screen> screens{ Screen(24,80,' ') };
};
Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s){
	screens.push_back(s);
	return screens.size() - 1;
}
void Window_mgr::clear(ScreenIndex i) { 
	Screen &s = screens[i];
	s.contents = string(s.height*s.width, ' ');
}
Screen::pos Screen::size() const {
	return height*width;
}
int main() {
	Screen myScreen(5, 5, 'x');//contants[h*w,'x']
	myScreen.move(1, 0).Set('`').display(cout);//cursor = 4*5，定义contants【20】 = ’·‘
	cout << myScreen.get() << '\n';
	myScreen.Set('#');
	myScreen.display(cout);
	system("pause");
}