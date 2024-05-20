#include <iostream>
using namespace std;

__interface IDataReader {
	virtual void Read() = 0;
};

class DataBaseReader : public IDataReader {
public:
	void Read() override {
		cout << "Data from DB...\n";
	}
};

class FileRrader : public IDataReader {
public:
	void Read() override {
		cout << "Data from file...\n";
	}
};

class Sender abstract {
protected:
	IDataReader* reader;
public:
	Sender(IDataReader* dr) : reader(dr){}
	void SetDataReader(IDataReader* dr) {
		reader = dr;
	}
	virtual void Send() = 0;
};

class EmailSender : public Sender {
public:
	EmailSender(IDataReader* dr) : Sender(dr){}
	void Send() override {
		reader->Read();
		cout << "Send with email...\n";
	}
};

class TelegramSender : public Sender {
public:
	TelegramSender(IDataReader* dr) : Sender(dr) {}
	void Send() override {
		reader->Read();
		cout << "Send with Telegram...\n";
	}
};

int main() {
	Sender* sender = new EmailSender(new DataBaseReader());
	sender->Send();
	sender->SetDataReader(new FileRrader());
	sender->Send();
	sender = new TelegramSender(new DataBaseReader());
	sender->Send();
}