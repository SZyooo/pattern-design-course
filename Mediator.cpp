#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Processable;
class Message{
public:
    Message(shared_ptr<Processable> processable)
        :_processable(processable){}
    virtual ~Message(){}
    
    virtual bool operator==(const Message& msg) const = 0;
    shared_ptr<Processable> GetProcessable(){
        return this->_processable;
    }
private:
    shared_ptr<Processable> _processable;
};

enum class MSGType{
    TEXT,
    IMAGE,
    EMOJI
};

class UserInput:public Message{
public:
    UserInput(shared_ptr<Processable> processable, MSGType type)
        :Message(processable),_type(type){}
    MSGType Type() const {return _type;}
    virtual bool operator==(const Message& u) const
    {
        const UserInput& ui = dynamic_cast<const UserInput&>(u);
        return _type == ui.Type();
    }
private:
    MSGType _type;
};

class Processable{
public:
    virtual ~Processable(){};
};
class Text: public Processable
{
public:
    Text(string txt):_content(txt){}
    string Content() const {return _content;}
private:
    string _content;
};
class Image: public Processable
{
public:
    Image(size_t size):_size(size){}
    size_t Size() const {return _size;}
private:
    size_t _size;
};
class Emoji:public Processable
{
public:
    Emoji(string exp):_facial_expression(exp){}
    string Expression() const {return _facial_expression;}
private:
    string _facial_expression;
};

class Processor{
public:
    virtual ~Processor(){}
    virtual void Process(const Processable&) = 0;
};
class TextProcessor: public Processor{
public:
    virtual void Process(const Processable& txt)
    {
        const Text& t = dynamic_cast<const Text&>(txt);
        cout << "print text" << t.Content() << endl;
    }
};
class ImageProcessor: public Processor{
public: 
    virtual void Process(const Processable& i)
    {
        const Image& img = dynamic_cast<const Image&>(i);
        cout << "the size of the image is" << img.Size() << endl;
    }
};

class EmojiProcessor: public Processor{
public:
    virtual void Process(const Processable& e)
    {
        const Emoji& emo = dynamic_cast<const Emoji&>(e);
        cout << "the facial expression of the emoji is" << emo.Expression() << endl;
    }
};


class Mediator{
public:
    virtual ~Mediator(){}
    virtual void Notify(Message& msg) = 0;
};

class MSGMediator: public Mediator{
public:
    virtual void Notify(Message& ui)
    {
        UserInput& msg = dynamic_cast<UserInput&>(ui);
        if(msg.Type() == MSGType::TEXT)
        {
            for(auto text:_text_processors)
            {
                Text& p = dynamic_cast<Text&>(*msg.GetProcessable());
                text->Process(p);
            }
        }
        else if(msg.Type() == MSGType::IMAGE)
        {
            for(auto image: _img_processors)
            {
                Image& img = dynamic_cast<Image&>(*msg.GetProcessable());
                image->Process(img);
            }
        }
        else if(msg.Type() == MSGType::EMOJI)
        {
            for(auto emo:_emo_processors)
            {
                Emoji& e = dynamic_cast<Emoji&>(*msg.GetProcessable());
                emo->Process(e);
            }
        }
    }
    void AddTextProcessor(shared_ptr<TextProcessor> processor)
    {
        _text_processors.push_back(processor);
    }
    void AddImageProcessor(shared_ptr<ImageProcessor> processor)
    {
        _img_processors.push_back(processor);
    }
    void AddEmojiProcessor(shared_ptr<EmojiProcessor> processor)
    {
        _emo_processors.push_back(processor);
    }
private:
    vector<shared_ptr<TextProcessor>> _text_processors;
    vector<shared_ptr<ImageProcessor>> _img_processors;
    vector<shared_ptr<EmojiProcessor>> _emo_processors;
};


int main()
{
    MSGMediator msgController;
    msgController.AddTextProcessor(shared_ptr<TextProcessor>(new TextProcessor()));
    msgController.AddImageProcessor(shared_ptr<ImageProcessor>(new ImageProcessor()));
    msgController.AddEmojiProcessor(shared_ptr<EmojiProcessor>(new EmojiProcessor()));
    
    UserInput in1(shared_ptr<Image>(new Image(128)),MSGType::IMAGE);
    UserInput in2(shared_ptr<Text>(new Text("Hello world")),MSGType::TEXT);
    UserInput in3(shared_ptr<Emoji>(new Emoji("Happy")),MSGType::EMOJI);
    msgController.Notify(in1);
    msgController.Notify(in2);
    msgController.Notify(in3);
    
    return 0;
}