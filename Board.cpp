#include "Board.h"

void Board::Draw(int _width, int _height, HANDLE _consoleHandle) {
    // Input: _width(chiều dài sàn đấu), _height(chiều rộng sàn đấu), _consoleHandle(con trỏ đại diện cho màn hình console)
    // Output: Không
    // Chức năng: Vẽ sàn đấu, điểm ban đầu của người chơi và máy

    for (int i = 0; i < _width - 1; ++i) { // Vòng lặp vẽ biên trên của sàn đấu
        cout << static_cast<char>(219);
    }

    for (int i = 0; i < _height - 1; ++i) {
        cout << endl << static_cast<char>(219);

        for (int j = 0; j < _width - 3; ++j) {
            cout << ' ';
        }

        cout << static_cast<char>(219);
    }

    cout << endl;

    for (int i = 0; i < _width - 1; ++i) {
        cout << static_cast<char>(219);
    }
}

void Board::Reset(Bar& _you, Ball& _b, vector<Block>& _block, vector<Barrier>& _barrier, bool& _start, int& y_Score, int _width, int _height, HANDLE _consoleHandle,int item_index) {
    // Input: _you(thanh hứng của bạn), _comp(thanh hứng của máy), _b(quả bóng), _start(biến kiểm tra trò chơi bắt đầu hay chưa),
    //          y_Score(điểm của bạn), c_Score(điểm của máy), _width(chiều rộng sàn đấu), _height(chiều dài sàn đấu),
    //          _consoleHandle(con trỏ đại diện cho màn hình console)
    // Output: Không
    // Chức năng: Reset game mỗi khi một trong hai thanh không hứng được quả bóng
    
    //xoa man hinh
	system("CLS");
    _b.SetX(float(_width / 2 - 1)); // Set tọa độ x của quả bóng là _witdh/2 - 1
    _b.SetY(float(_height / 2)); // Set tạo độ y của quả bóng là _height/2
    _b.SetVx(float(rand() % 3) - 1.5f); // Set tốc độ của quả bóng theo trục Ox
    _b.SetVy(1); // Set tốc độ của quả bóng theo trục Oy
    
    _you.SetX(float(_width / 2)); // Set tọa độ x của thanh hứng của người chơi là _width/2
    
    for (int i = 0; i < _block.size(); i++)
        _block[i].setIsCrash(false);
    for (int i = 0; i < _barrier.size(); i++)
        _barrier[i].setIsExist(false);

    _start = false; // Đặt biến kiểm tra về trạng thái chưa bắt đầu
    y_Score = 0;
	item_index = 0;
    this->Draw(_width, _height, _consoleHandle);
    _you.Draw(_consoleHandle); // Vẽ thanh trượt của người chơi
    _b.Draw(_consoleHandle); // Vẽ quả bóng
}

void Board::Run(Bar& _you, Ball& _b, vector<Block>& _block, vector<Barrier>& _barrier, bool& _start, int& y_Score, int _width, int _height, HANDLE _consoleHandle, int _maxSpeed,vector<string>& his) {
    // Input: _you(thanh hứng của bạn), _comp(thanh hứng của máy), _b(quả bóng), _start(biến kiểm tra trò chơi bắt đầu hay chưa),
    //          y_Score(điểm của bạn), c_Score(điểm của máy), _width(chiều rộng sàn đấu), _height(chiều dài sàn đấu),
    //          _consoleHandle(con trỏ đại diện cho màn hình console), _maxSpeed(tốc độ tối đa)
    // Output:
    // Chức năng: Hoạt động của trò chơi đến khi không hứng được quả bóng
    int count_block = 0;
	COORD _p;
	_p.X = int(_width / 2 - 16);
	_p.Y = int(_height / 1.5f);
	Item item;
	clock_t itemStart = clock();
	clock_t timeStart = clock();
	int barr_index = -1;
	int item_index = 0;
	int check = 0;
	bool checkitem = false;
	vector<clock_t> time;
    while (true) {

        if (_start) {
			if ((clock()-timeStart)/CLOCKS_PER_SEC % 15 == 0 && (clock() - timeStart) / CLOCKS_PER_SEC >1 && check ==0) {
				barr_index++;
				_barrier[barr_index].setIsExist(true);
				check = 1;
			}
			if ((clock() - timeStart) / CLOCKS_PER_SEC % 15 == 1) { check = 0; }

            // Khi người chơi nhấn phím mũi tên qua lại
            if (GetAsyncKeyState(VK_LEFT)) { // Khi nhấn phím mũi tên qua trái
                float _x = _you.GetX(); // Get tọa độ x của thanh trượt
                _x -= 2; // Tọa độ x mới của thanh trượt
                _you.SetX(_x); // Set tọa độ x mới của thanh trượt sau khi dịch qua trái 2 đơn vị
            }
            else if (GetAsyncKeyState(VK_RIGHT)) { // Khi phím mũi tên qua phải
                float _x = _you.GetX(); // Get tọa độ x của thanh trượt
                _x += 2; // Tọa độ x mới của thanh trượt
                _you.SetX(_x); // Set tọa độ x mới của thanh trượt sau khi dịch qua phải 2 đơn vị đo
            }
			else if (GetAsyncKeyState(0x53)) {
				time = SaveGame(_b, _you, _block, barr_index, item, y_Score, timeStart, itemStart, _height, _consoleHandle, item_index, checkitem);
				timeStart = time[0] + clock();
				itemStart = time[1] + clock();
			}

            // Thêm ràng buộc để thanh trượt của người chơi không thể đi ra khỏi sàn đấu
            if (_you.GetX() < _you.GetSize() + 1) { // Kiểm tra nếu ra khỏi sàn đấu bên viền trái chưa
                _you.SetX(float(_you.GetSize() + 1)); // Nếu ra khỏi thì Set lại tọa độ X để thanh trượt sát viền
            }
            else if (_you.GetX() > _width - _you.GetSize() - 2) { // Kiểm tra nếu ra khỏi sàn đấu bên viền phải chưa
                _you.SetX(float(_width - _you.GetSize() - 2));// Nếu ra khỏi thì Set lại tọa độ X để thanh trượt sát viền
            }

            // Ràng buộc để quả bóng không thể vượt quá vận tốc tối đa
            if (_b.GetVx() < -_maxSpeed) {
                _b.SetVx(-_maxSpeed);
            }
            else if (_b.GetVx() > _maxSpeed) {
                _b.SetVx(_maxSpeed);
            }

            // Dùng vận tốc Vx, Vy của quả bóng để tính vị trí hiện tại của quả bóng
            _b.SetX(_b.GetX() + _b.GetVx()); // Set tọa độ X bằng vị trí cũ của bóng cộng với vận tốc Vx
            _b.SetY(_b.GetY() + _b.GetVy()); // Set tọa độ Y bằng vị trí cũ của bóng cộng với vận tốc Vy

            // Kiểm tra nếu thanh trượt của người chơi chạm (hứng) được quả bóng
            if (_b.GetY() >= _you.GetY() - 1 && _b.GetY() <= _you.GetY() + 1) {
                // Kiểm tra tọa độ Y của quả bóng có thuộc đoạn độ cao với tọa độ Y của thanh trượt

                if (_b.GetX() >= _you.GetX() - _you.GetSize() && _b.GetX() <= _you.GetX() + _you.GetSize()) {
                    // Kiểm tra xem tọa độ X của bóng có nằm trên thanh trượt hay không

                    _b.SetVy(_b.GetVy() * -1); // Set vận tốc Vy của bóng cho đi ngược lại
                    _b.SetVx(_b.GetVx() + float(_b.GetX() - _you.GetX()) / 3); // Set vận tốc Vx của bóng vừa tăng sau khi chạm vào thanh trượt
                    _b.SetY(_you.GetY() - 1); // Set tọa độ Y của bóng lúc bật lại
                }
            }
            
			for (int i = 0; i < _block.size(); i++) {
				if (!_block[i].getIsCrash()) {
					if (_b.GetX() >= _block[i].GetX() - _block[i].GetSize() && _b.GetX() <= _block[i].GetX() + _block[i].GetSize()) {
						if (_b.GetY() > _block[i].GetY() - 1 && _b.GetY() < _block[i].GetY() + 1) {
							_b.SetY(_block[i].GetY() - _b.GetVy() / abs(_b.GetVy()));
							_b.SetVy(_b.GetVy() * -1); // Set vận tốc Vy của bóng cho đi ngược lại
							y_Score += 10;
							_block[i].setIsCrash(true);
							count_block++;
						}
					}

					if (_b.GetY() < _block[i].GetY() + 1 && _b.GetY() > _block[i].GetY() - 1) {
						if (_b.GetX() > _block[i].GetX() - _block[i].GetSize() - 1 && _b.GetX() < _block[i].GetX() - _block[i].GetSize() + 1) {
							_b.SetVx(_b.GetVx() * -1);
							_b.SetX(_block[i].GetX() - _block[i].GetSize() - 1);
							y_Score += 10;
							_block[i].setIsCrash(true);
							count_block++;
						}
						if (_b.GetX() < _block[i].GetX() + _block[i].GetSize() + 1 && _b.GetX() > _block[i].GetX() + _block[i].GetSize() - 1) {
							_b.SetVx(_b.GetVx() * -1);
							_b.SetX(_block[i].GetX() + _block[i].GetSize() + 1);
							y_Score += 10;
							_block[i].setIsCrash(true);
							count_block++;
						}
					}
				}
			}
            
			for (int i = 0; i < _barrier.size(); i++) {
				if (_barrier[i].getIsExist()) {
					if (_b.GetX() >= _barrier[i].GetX() - _barrier[i].GetSize() && _b.GetX() <= _barrier[i].GetX() + _barrier[i].GetSize()) {
						if (_b.GetY() > _barrier[i].GetY() - 1 && _b.GetY() < _barrier[i].GetY() + 1) {
							_b.SetY(_barrier[i].GetY() - _b.GetVy() / abs(_b.GetVy()));
							_b.SetVy(_b.GetVy() * -1);
						}
					}

					if (_b.GetY() < _barrier[i].GetY() + 1 && _b.GetY() > _barrier[i].GetY() - 1) {
						if (_b.GetX() < _barrier[i].GetX() + _barrier[i].GetSize() + 1 && _b.GetX() > _barrier[i].GetX() + _barrier[i].GetSize() - 1) {
							_b.SetVx(_b.GetVx() * -1);
							_b.SetX(_barrier[i].GetX() + _barrier[i].GetSize() + 1);
						}
					}
				}
			}

			// Khi quả bóng chạm biên trái, phải
			if (_b.GetX() <= 1) { // Khi chạm biên trái
				_b.SetVx(_b.GetVx() * -1); // Bật ngược lại
				_b.SetX(1.0f);
			}
			else if (_b.GetX() >= _width - 3) { // Khi chạm biên phải
				_b.SetVx(_b.GetVx() * -1); // bật ngược lại
				_b.SetX(float(_width - 3));
			}
			else if (_b.GetY() <= 1) {
				_b.SetVy(_b.GetVy() * -1); // Bật ngược lại
				_b.SetY(1.0f);
			}

			_you.Draw(_consoleHandle); // Vẽ thanh trượt của người chơi
			_b.Draw(_consoleHandle); // Vẽ quả bóng
			for (int i = 0; i < _block.size(); i++) {
				_block[i].Draw(_consoleHandle, i + 1);
			}
			for (int i = 0; i < _barrier.size(); i++) {
				_barrier[i].Draw(_consoleHandle);
			}

            COORD _p;

			_p.X = 0;
			_p.Y = _height;

			SetConsoleCursorPosition(_consoleHandle, _p); // Đưa con trỏ tới vị trí _pos(0, _height)
			cout << endl << " Diem cua ban : " << y_Score << endl; // In ra màn hình điểm của bạn 

            _p.X = int(_width / 2 - 16);
            _p.Y = int(_height / 1.5f);

            // Khi không hứng được quả bóng
            if (_b.GetY() > _height - 2 || _barrier[_barrier.size() - 1].getIsExist()) { // Kiểm tra khi người chơi không hứng được bóng
                SetConsoleCursorPosition(_consoleHandle, _p);
                cout << "You lose!\tYour score: " << y_Score;
				
				writeHis(his, false, y_Score, 120);

				_p.Y += 1;
				SetConsoleCursorPosition(_consoleHandle, _p);
				system("pause");
                this->Reset(_you, _b, _block, _barrier, _start, y_Score, _width, _height, _consoleHandle,item_index);
            }
            if (checkWin(_block)){
                SetConsoleCursorPosition(_consoleHandle, _p);
                cout << "You win!\tYour score: " << y_Score;

				writeHis(his, true, y_Score, 120);

				_p.Y += 1;
				SetConsoleCursorPosition(_consoleHandle, _p);
				system("pause");
                this->Reset(_you, _b, _block, _barrier, _start, y_Score, _width, _height, _consoleHandle,item_index);
            }

			if (item_index == 0) {
				if (rand() % 50 == 5 && (clock() - itemStart) / CLOCKS_PER_SEC > 2 && ((clock() - itemStart) / CLOCKS_PER_SEC) % 2 == 0) {
					item.Draw(itemStart, _consoleHandle);
					item_index = 1;
					checkitem = true;
				}
			}
			else {
				if (rand() % 50 == 5 && (clock() - itemStart) / CLOCKS_PER_SEC > 12 && ((clock() - itemStart) / CLOCKS_PER_SEC) % 2 == 0) {
					item.renewItem();
					checkitem = false;
				}
				if (checkitem == false) {
					item.Draw(itemStart, _consoleHandle);
					checkitem = true;
				}
				if (item.checkTime(itemStart, _consoleHandle) == false) {
					item.~Item();
				}
			}
			if (item.checkEat(_b) &&item.getIsExict() == true) {
				COORD _pos;
				_pos.X = item.getX();
				_pos.Y = item.getY();

				SetConsoleCursorPosition(_consoleHandle, _pos); // dua con tro toi vi tri moi cua bong
				SetConsoleTextAttribute(_consoleHandle, 12);
				cout << "  ";
				_pos.X = item.getX();
				_pos.Y = item.getY()+1;
				SetConsoleCursorPosition(_consoleHandle, _pos);
				cout << "  ";
				SetConsoleTextAttribute(_consoleHandle, 15);
				item.setIsExict(false);
				item.EffectOfItem(y_Score);
				//checkitem = false;
			}
        }
        else {
		_you.Draw(_consoleHandle); // Vẽ thanh trượt của người chơi
		_b.Draw(_consoleHandle); // Vẽ quả bóng
		for (int i = 0; i < _block.size(); i++) {
			_block[i].Draw(_consoleHandle, i + 1);
		}
		for (int i = 0; i < _barrier.size(); i++) {
			_barrier[i].Draw(_consoleHandle);
		}

		his = readHis();
		// Đợi người chơi bắt đầu màn mới bằng nút space
		COORD _pos; // Tọa độ _pos
		barr_index = -1;
		_pos.X = int(_width / 2 - 16);
		_pos.Y = int(_height / 1.5f);

		SetConsoleCursorPosition(_consoleHandle, _pos); // Đưa con trở tới vị trí _pos(_width/2-16, _height/1.5f)
		cout << "Nhan phim 'space' de bat dau!";

		_pos.X = int(_width / 2 - 16);
		_pos.Y++;

		SetConsoleCursorPosition(_consoleHandle, _pos); // Đưa con trở tới vị trí _pos(_width/2-16, _height/1.5f)
		cout << "Nhan phim 'H' de xem lich su";

		_pos.X = int(_width / 2 - 16);
		_pos.Y++;

		SetConsoleCursorPosition(_consoleHandle, _pos); // Đưa con trở tới vị trí _pos(_width/2-16, _height/1.5f)
		cout << "Nhan phim 'L' de LoadGame";

		if (GetAsyncKeyState(VK_SPACE)) { // Khi người chời bắt đầu
			SetConsoleCursorPosition(_consoleHandle, _pos); // Đưa con trỏ tới vị trí _pos(_width/2-16, _height/1.5f)
			cout << "                                "; // Xóa câu "Nhấn phím 'space' để bắt đầu!"

			_pos.Y--;
			SetConsoleCursorPosition(_consoleHandle, _pos); // Đưa con trỏ tới vị trí _pos(_width/2-16, _height/1.5f)
			cout << "                                ";

			_pos.Y--;
			SetConsoleCursorPosition(_consoleHandle, _pos); // Đưa con trỏ tới vị trí _pos(_width/2-16, _height/1.5f)
			cout << "                                ";

			COORD _p1;
			_p1.X = 0;
			_p1.Y = _height;

			SetConsoleCursorPosition(_consoleHandle, _p1); // Đưa con trỏ tới vị trí _p1(0, _height)
			cout << endl << " Diem cua ban : " << y_Score << endl; // In lại điểm

			_start = true;//biến kiểm tra điều kiện để bắt đầu
		}
		else if (GetAsyncKeyState(0x48)) {
			showHis(his, _width, _height, _consoleHandle);
			system("pause");
			system("CLS");
			_pos.X = 0;
			_pos.Y = 0;

			SetConsoleCursorPosition(_consoleHandle, _pos);
			_start = true;
			Draw(_width, _height, _consoleHandle);// Vẽ sàn đấu
		}
		else if (GetAsyncKeyState(0x4C)) {
			LoadGame(_b, _you, _block, _barrier, item, barr_index, y_Score, timeStart, _height, _consoleHandle,item_index,checkitem,itemStart);
			_start = true;
			//if (item.getIsExict()) item.Draw(itemStart,_consoleHandle);
			Draw(_width, _height, _consoleHandle);
			if (item.getIsExict()) item.Draw(itemStart, _consoleHandle);
		}
		timeStart = clock();
		}
		

		// Delay
		Sleep(50);
    }
}

vector<clock_t> Board::SaveGame(Ball ball, Bar bar, vector<Block> block, int barr_index, Item item, int score, clock_t timeStart, clock_t timeItem, int _height, HANDLE _consoleHandle,int itemIndex, bool checkItem) {
	string file;
	vector<clock_t> time;
	time.push_back(timeStart);
	time.push_back(timeItem);

	COORD _pos; // Tọa độ _pos

	_pos.X = 0;
	_pos.Y = _height  + 2;

	SetConsoleCursorPosition(_consoleHandle, _pos);
	cout << "Nhap ten tap tin can luu: ";
	cin >> file;

	regex pattern("[a-zA-Z0-9]+(\.txt){1}$");
	if (regex_match(file, pattern) == false) {
		cout << "\tTen tap tin khong hop le!";
		return time;
	}

	ofstream os(file, ios::trunc);
	if (!os) {
		cout << "\tKhong the mo tap tin" << endl;
		return time;
	}
	SetConsoleCursorPosition(_consoleHandle, _pos);
	cout << "                                                                          ";

	os << item.getX() << " " << item.getY() << " " << item.getType() << " " << itemIndex << " " << checkItem << " ";
	if (item.getIsExict())
		os << "1" << endl;
	else
		os << "0" << endl;

	os << ball.GetX() << " " << ball.GetY() << " " << ball.GetVx() << " " << ball.GetVy() << endl;

	os << bar.GetX() << " " << bar.GetY() << endl;

	os << score << " " << timeStart <<" " << timeItem << endl;
	for (int i = 0; i < block.size(); i++) {
		if (block[i].getIsCrash())
			os << "1 ";
		else
			os << "0 ";
	}
	os << endl;
	
	os << barr_index;

	os.close();
	return time;
}

void Board::LoadGame(Ball& ball, Bar& bar, vector<Block>& block, vector<Barrier>& barr, Item& item, int& barr_index, int& score, clock_t& time, int& _height, HANDLE& _consoleHandle, int& itemIndex, bool& checkItem, clock_t& itemStart) {
    string file;
	COORD _pos; // Tọa độ _pos

	_pos.X = int(9);
	_pos.Y = int(_height / 1.5f) + 3;

	SetConsoleCursorPosition(_consoleHandle, _pos);
	cout << "Nhap ten tap tin can load: ";
	cin >> file;

	regex pattern("[a-zA-Z0-9]+(\.txt){1}$");
	if (regex_match(file, pattern) == false) {
		cout << "\tTen tap tin khong hop le!";
		return;
	}

    ifstream fs(file);
    if (fs.fail()) {
        cout << "\tKhong the mo tap tin!";
        return;
    }

	SetConsoleCursorPosition(_consoleHandle, _pos);
    cout << "                                   ";
    

    float ball_x, ball_y, ball_vx, ball_vy;
    float bar_x, bar_y;
	int item_x, item_y, item_type, check;

	fs >> item_x >> item_y >> item_type >> check >> itemIndex >> checkItem;
	item.setX(item_x);
	item.setY(item_y);
	item.setType(item_type);
	if (check == 1)
		item.setIsExict(true);
	else
		item.setIsExict(false);

    fs >> ball_x >> ball_y >> ball_vx >> ball_vy;
	ball.SetX(ball_x);
	ball.SetY(ball_y);
	ball.SetVx(ball_vx);
	ball.SetVy(ball_vy);

    fs >> bar_x >> bar_y;
	bar.SetX(bar_x);
	bar.SetY(bar_y);

    fs >> score >> time >> itemStart;

	for (int i = 0; i < block.size(); i++) {
		fs >> check;
		if (check == 1)
			block[i].setIsCrash(true);
		else
			block[i].setIsCrash(false);
	}

	fs >> barr_index;

	for (int i = 0; i < barr.size(); i++) {
		if (i <= barr_index)
			barr[i].setIsExist(true);
		else
			barr[i].setIsExist(false);
	}

    fs.close();
	system("CLS");
}
void Board::writeHis(vector<string>& his, bool check, int score, int time) {
	string line = "";

	if (check == true)
		line += "win\t\t";
	else
		line += "lose\t\t";

	line = line + to_string(score) + "\t\t" + to_string(time);
	his.push_back(line);

	ofstream os("history.txt", ios::trunc);
	if (!os) {
		cout << "\tKhong the mo tap tin" << endl;
		return;
	}

	for (int i = 0; i < his.size(); i++) {
		os << his[i] << endl;
	}

	os.close();
}

vector<string> Board::readHis() {
	vector<string> his;
	string line;

	ifstream fs("history.txt");
	if (fs.fail()) {
		cout << "\tKhong the mo tap tin!";
		return his;
	}

	while (!fs.eof()) {
		getline(fs, line);

		if (line == "")
			break;

		his.push_back(line);
	}

	fs.close();
	return his;
}

void Board::showHis(vector<string> his,int _width, int _height, HANDLE _consoleHandle) {
	system("CLS");
	COORD _pos;

	_pos.X = int(_width / 2 - 8);
	_pos.Y = int(_height / 2 - 10);

	SetConsoleCursorPosition(_consoleHandle, _pos);
	cout << "Lich su da choi";

	_pos.X = int(5);
	_pos.Y++;
	SetConsoleCursorPosition(_consoleHandle, _pos);
	cout << "Status\t\tScore\t\tTime";

	int n = 0;
	if (his.size() >= 10)
		n = his.size() - 10;

	for (int i = his.size() - 1; i >= n; i--) {
		_pos.X = int(5);
		_pos.Y++;
		SetConsoleCursorPosition(_consoleHandle, _pos);
		cout << his[i];
	}
	cout << endl;
}

bool Board::checkWin(vector<Block> b) {
	for (int i = 0; i < b.size(); i++) {
		if (!b[i].getIsCrash())
			return false;
	}
	return true;
}

void Board::PauseGame(HANDLE t) {
    SuspendThread(t);
}

Board::Board() {

}

Board::~Board() {

}
