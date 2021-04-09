#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;


template <class T>
class DoublyLL
{
public:
    class Node;
    class Iterator;
protected:
    Node* head;
    Node* tail;
    int maxTinR;
    int count;
public:
    DoublyLL(int maxTinR = 5)
    {
        this->count = 0;
        this->maxTinR = maxTinR;
        this->head = NULL;
        this->tail = NULL;
    }
    ~DoublyLL()
    {
        //clear;
    }
    void add(const T& element)
    {
        if (empty())
        {
            this->head = new Node(element, NULL, NULL);
            this->tail = this->head;
            this->count = 1;
        }
        else
        {
            this->head->prev = new Node(element, NULL, this->head);
            this->head = this->head->prev; this->count++;
        }
    }
    void removeAt(Node* temp)
    {
        if (temp == head)
        {
            this->head = this->head->next;
            delete temp;
        }
        else if (temp == tail)
        {
            this->tail = this->tail->prev;
            delete temp;
        }
        else
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
        this->count--;
    }
    bool empty()
    {
        if (this->count == 0) return true;
        return false;
    }
    int size()
    {
        return this->count;
    }
    void clear()
    {
        if (empty()) return;
        Node* temp = this->head;
        while (!tail)
        {
            Node* camp = temp;
            temp = temp->next;
            delete camp;
        }
        this->count = 0;
    }
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
    class Node
    {
    private:
        T data;
        Node* prev;
        Node* next;
        friend class DoublyLL<T>;
    public:
        Node()
        {
            next = 0;
            prev = 0;
        }
        Node(Node* prev, Node* next)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node* prev, Node* next)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    private:
        DoublyLL<T>* pList;
        Node* pNode;
        int index;
    public:
        Iterator(DoublyLL<T>* pList = 0, bool begin = true)
        {
            this->index = 0;
            this->pList = pList;
            if (this->pList->head == nullptr) return;
            if (begin) this->pNode = pList->head;
            else this->pNode = pList->tail->next;
        }
        Iterator& operator=(const Iterator& iterator)
        {
            this->pNode = iterator.pNode;
            this->index = iterator.index;
            return *this;
        }
        T& operator*()
        {
            if (!this->pNode)
            {
                throw std::out_of_range("Segmentation fault!");
            }
            return this->pNode->data;
        }
        bool operator!= (const Iterator& iterator)
        {
            return !(this->pNode == iterator.pNode);
        }
        Iterator& operator++()
        {
            if ((this->pNode))
            {
                this->pNode = this->pNode->next;
                this->index += 1;
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator temp = *this;
            if ((this->pNode))
            {
                this->pNode = this->pNode->next;
                this->index += 1;
            }
            return temp;
        }
        void remove()
        {
            Node* temp = this->pNode;
            if (this->pNode == this->pList->tail)
            {
                this->pNode = this->pNode->prev;
                this->index--;
            }
            else this->pNode = this->pNode->next;
            try
            {
                this->pList->removeAt(temp);
            }
            catch (const char* msg)
            {
                cerr << msg << endl;
            }
        }
    };
};




enum CMD {SQ = 1,INS = 2,DEL = 3,CS = 4,CE = 5,GS = 6,GE = 7 };

CMD convert(const string& str)
{
    string s = str.substr(0,str.find(" ") + 1);
    if (s == "SQ ") return SQ;
    if (s == "INS ") return INS;
    if (s == "DEL ") return DEL;
    if (s == "CS ") return CS;
    if (s == "CE ") return CE;
    if (s == "GS ") return GS;
    if (s == "GE ") return GE;
    else return SQ;
}





class BusSystem {
public:
    struct time
    {
        int hour;
        int minute;
    };
    class busRoute;
    class busTrip;
protected:
    DoublyLL <busRoute> Route;
    int maxTinR;
    int num;
public:
    BusSystem(int maxTinR = 5)
    {
        this->maxTinR = maxTinR;
        this->num = 0;
    }
    ~BusSystem()
    {

    }
    string query(string instruction) {
        return readCMD(instruction);
    }
    string readCMD(string& str)
    {
        if (numString(str) == -1) return "-1";
        string s = str.substr(str.find(" ") + 1);
        string a = str.substr(s.length());
        CMD cmd; stringstream ss; string ret;
        cmd = convert(str);
        switch (cmd)
        {
        case SQ:
            if (SQsyn(s))
            {
                this->maxTinR = SQsyn(s);
                return "1";
            }
            else return "-1";
            break;
        case INS:
            ss << INSsyn(s); ret = ss.str();
            return ret;
            break;
        case DEL:
            //stringstream ss;
            ss << DELsyn(s); ret = ss.str();
            return ret;
            break;
        case CS:
            //stringstream ss;
            ss << CScmd(s); ret = ss.str();
            return ret;
            break;
        case CE:
            //stringstream ss;
            ss << CEcmd(s); ret = ss.str();
            return ret;
            break;
        case GS:
            return GScmd(s);
            break;
        case GE:
            return GEcmd(s);
            break;
        default:
            return "-1";
            break;
        }
    }

    int numString(string& s)
    {
        int count = 0;
        for (auto it = s.begin(); it != s.end(); it++)
        {
            if (*it == ' ')
            {
                if (it != s.begin() && it != s.end() - 1)
                {
                    count += 1; auto temp = it + 1;
                    if ((*temp) == ' ') return 0;
                }
                else return 0;
            }
        }
        return count;
    }
    int SQsyn(string& s)
    {
        stringstream ss(s); int x = 0;
        ss >> x;
        if (x == 0 || numString(s) != 0) return -1;
        return x;
    }
    int INSsyn(string& s)
    {
        bool c;
        //int a = numString(s);
        if (numString(s) == 4) c = true;
        else if (numString(s) == 3) c = false;
        else return -1;
        int Case = 0; string tA; string tB;
        string cde = s.substr(0, s.find(" ") + 1); // take the code
        s = s.substr(cde.length());
        string lp = s.substr(0, s.find(" ") + 1); //take lp
        s = s.substr(lp.length());
        string tmp = s.substr(0, s.find(" ") + 1);
        if (c == true)
        {
            if (tmp == "0 " || tmp == "1 ")
            {
                stringstream ss(tmp);
                ss >> Case; // get the case
            }
            else return -1;
            s = s.substr(tmp.length());
            tA = s.substr(0, s.find(" ") + 1);
            s = s.substr(tA.length());
            tB = s;
        }
        else
        {
            tA = tmp;
            s = s.substr(tA.length());
            tB = s;
        }
        tA = tA.substr(0, tA.find(" "));
        // Should break down
        time A = StoT(tA); time B = StoT(tB);
        if (timeCmp(A, B) != -1) return -1;
        if (this->Route.empty())
        {
            busRoute R; busTrip T;
            R.code = cde.substr(0, cde.find(" "));
            T.CASE = Case;
            T.LP = lp.substr(0, lp.find(" "));
            T.timeA = A;
            T.timeB = B;
            R.Trip.add(T);
            this->Route.add(R); this->num++;
            return this->num;
        }
        else
        {
            bool check = false; bool valid = true;
            for (DoublyLL<busRoute>::Iterator it = this->Route.begin(); it != this->Route.end();it++)
            {
                if ((*it).code == cde.substr(0, cde.find(" ")))
                {
                    if ((*it).Trip.size() > this->maxTinR)
                    {
                        valid = false; break;
                    }
                    time temp; temp.hour = 0; temp.minute = 0; time tempx; tempx.hour = 0; tempx.minute = 0;
                    time camp; camp.hour = 99; temp.minute = 99; time campx; campx.hour = 0; campx.minute = 0;
                    for (DoublyLL<busTrip>::Iterator ot = (*it).Trip.begin(); ot != (*it).Trip.end(); ot++)
                    {
                        if ((*ot).LP == lp.substr(0, lp.find(" ")))
                        {
                            if (timeCmp((*ot).timeB, temp) == 1)
                            {
                                temp = (*ot).timeB;
                                tempx = (*ot).timeA;
                            }
                            if (timeCmp((*ot).timeA, camp) == -1)
                            {
                                camp = (*ot).timeA;
                                campx = (*ot).timeB;
                            }
                        }
                    }
                    if (timeCmp(A, temp) != 1 && timeCmp(tempx,B) != 1)
                    {
                        valid = false; break;
                    }
                    else if (timeCmp(camp, A) != 1 && timeCmp(B, campx) != 1)
                    {
                        valid = false; break;
                    }
                    busTrip T;
                    T.CASE = Case;
                    T.LP = lp.substr(0, lp.find(" "));
                    T.timeA = A;
                    T.timeB = B;
                    (*it).Trip.add(T);
                    check = true; this->num++;
                    return this->num; break;
                }
            }
            if (check == false && valid == true)
            {
                busRoute R; busTrip T;
                R.code = cde.substr(0, cde.find(" "));
                T.CASE = Case;
                T.LP = lp.substr(0, lp.find(" "));
                T.timeA = StoT(tA);
                T.timeB = StoT(tB);
                R.Trip.add(T);
                this->Route.add(R); this->num++;
                return this->num;
            }
        }
        return -1;
    }
    int DELsyn(string &s)
    {
        bool c; int count = 0;
        if (numString(s) != 2) return 0;
        string cde = s.substr(0, s.find(" ") + 1); // take the code
        s = s.substr(cde.length());
        string tA = s.substr(0, s.find(" ") + 1); // take the timeA
        s = s.substr(tA.length());
        string tB = s; // take the timeB
        tA = tA.substr(0, tA.find(" "));
        time A = StoT(tA); time B = StoT(tB);
        if (timeCmp(A, B) > 0) return 0;
        DoublyLL<busRoute>::Iterator it;
        DoublyLL<busTrip>::Iterator ot;
        // Should break down
        if (!this->Route.empty())
        {
            for (it = this->Route.begin(); it != this->Route.end(); it++)
            {
                if ((*it).code == cde.substr(0, cde.find(" ")))
                {
                    break;
                }
            }
            if (!(*it).Trip.empty())
            {
                for (ot = (*it).Trip.begin(); ot != (*it).Trip.end(); ot++)
                {
                    if (timeCmp((*ot).timeA,A) == 1 && timeCmp((*ot).timeB,B) == -1)
                    {
                        ot.remove(); count += 1;
                    }
                }
            }
        }
        this->num -= count;
        return count;
    }
    int CScmd(string& s)
    {
        bool c; int count = 0;
        if (numString(s) == 2) c = true;
        else if (numString(s) == 1) c = false;
        else return count;
        string cde = s.substr(0, s.find(" ") + 1); // take the code
        s = s.substr(cde.length()); time T;
        if (c == false)
        {
            T = StoT(s);
        }
        else
        {
            string t = s.substr(0, s.find(" ") + 1);
            s = s.substr(t.length());
            t = t.substr(0, t.find(" ")); T = StoT(t);
        }
        if (c == true)
        {
            if (s == "0" || s == "1")
            {
                stringstream ss(s); bool x ;
                ss >> x; // take the case
                for (DoublyLL<busRoute>::Iterator it = this->Route.begin(); it != this->Route.end(); it++)
                {
                    if ((*it).code == cde.substr(0, cde.find(" ")))
                    {
                       for (DoublyLL<busTrip>::Iterator ot = (*it).Trip.begin(); ot != (*it).Trip.end(); ot++)
                       {
                           if (timeCmp((*ot).timeB, T) >= 0 && (*ot).CASE == x)
                           {
                              count += 1;
                           }
                       }
                         break;
                    }
                }
            }
        }
        else
        {
            for (DoublyLL<busRoute>::Iterator it = this->Route.begin(); it != this->Route.end(); it++)
            {
                if ((*it).code == cde.substr(0, cde.find(" ")))
                {
                    for (DoublyLL<busTrip>::Iterator ot = (*it).Trip.begin(); ot != (*it).Trip.end(); ot++)
                    {
                        if (timeCmp((*ot).timeB, T) >= 0 && timeCmp(T,(*ot).timeA) == 1)
                        {
                            count += 1;
                        }
                    }
                    break;
                }
            }
        }
        return count;
    }
    
    int CEcmd(string& s)
    {
        bool c; int count = 0;
        if (numString(s) == 2) c = true;
        else if (numString(s) == 1) c = false;
        else return count;
        string cde = s.substr(0, s.find(" ") + 1); // take the code
        s = s.substr(cde.length()); time T;
        if (c == false)
        {
            T = StoT(s);
        }
        else
        {
            string t = s.substr(0, s.find(" ") + 1);
            s = s.substr(t.length());
            t = t.substr(0, t.find(" ")); T = StoT(t);
        }
        if (c == true)
        {
            if (s == "0" || s == "1")
            {
                stringstream ss(s); bool x;
                ss >> x; // take the case
                for (DoublyLL<busRoute>::Iterator it = this->Route.begin(); it != this->Route.end(); it++)
                {
                    if ((*it).code == cde.substr(0, cde.find(" ")))
                    {
                        for (DoublyLL<busTrip>::Iterator ot = (*it).Trip.begin(); ot != (*it).Trip.end(); ot++)
                        {
                            if (timeCmp((*ot).timeB, T) == -1 && (*ot).CASE == x)
                            {
                                count += 1;
                            }
                        }
                        break;
                    }
                }
            }
        }
        else
        {
            for (DoublyLL<busRoute>::Iterator it = this->Route.begin(); it != this->Route.end(); it++)
            {
                if ((*it).code == cde.substr(0, cde.find(" ")))
                {
                    for (DoublyLL<busTrip>::Iterator ot = (*it).Trip.begin(); ot != (*it).Trip.end(); ot++)
                    {
                        if (timeCmp((*ot).timeB, T) == -1)
                        {
                            count += 1;
                        }
                    }
                    break;
                }
            }
        }
        return count;
    }

    string GScmd(string& s)
    {
        bool c; int minDiff = 10000; string keep = "/0";
        if (numString(s) == 2) c = true;
        else if (numString(s) == 1) c = false;
        else return keep;
        string cde = s.substr(0, s.find(" ") + 1); // take the code
        s = s.substr(cde.length()); time T;
        if (c == false)
        {
            T = StoT(s);
        }
        else
        {
            string t = s.substr(0, s.find(" ") + 1);
            s = s.substr(t.length());
            t = t.substr(0, t.find(" ")); T = StoT(t);
        }
        if (c == true)
        {
            if (s == "0" || s == "1")
            {
                stringstream ss(s); bool x;
                ss >> x; // take the case
                //minDiff = TtoI((*(*this->Route.begin()).Trip.begin()).timeA) - TtoI(T);
                //keep = (*(*this->Route.begin()).Trip.begin()).LP;
                if (minDiff < 1) minDiff *= -1;
                for (DoublyLL<busRoute>::Iterator it = this->Route.begin(); it != this->Route.end(); it++)
                {
                    if ((*it).code == cde.substr(0, cde.find(" ")))
                    {
                        for (DoublyLL<busTrip>::Iterator ot = (*it).Trip.begin(); ot != (*it).Trip.end(); ot++)
                        {
                            int temp = TtoI((*ot).timeA) - TtoI(T);
                            if (temp < 0) temp *= -1;
                            if (temp <= minDiff && (*ot).CASE == x)
                            {
                                minDiff = temp;
                                keep = (*ot).LP;
                            }
                        }
                        if (keep == "/0") return "-1";
                        break;
                    }
                }
            }
        }
        else
        {
            for (DoublyLL<busRoute>::Iterator it = this->Route.begin(); it != this->Route.end(); it++)
            {
                if ((*it).code == cde.substr(0, cde.find(" ")))
                {
                    for (DoublyLL<busTrip>::Iterator ot = (*it).Trip.begin(); ot != (*it).Trip.end(); ot++)
                        {
                            int temp = TtoI((*ot).timeA) - TtoI(T);
                            if (temp < 0) temp *= -1;
                            if (temp <= minDiff)
                            {
                                if (temp == minDiff && (*ot).CASE == 0)
                                {
                                    minDiff = temp;
                                    keep = (*ot).LP;
                                }
                                else if (temp < minDiff)
                                {
                                    minDiff = temp;
                                    keep = (*ot).LP;
                                }
                            }
                        }
                    if (keep == "/0") return "-1";
                    break;
                }
            }
        }
        return keep;
    }

    string GEcmd(string& s)
    {
        bool c; int minDiff = 10000; string keep = "/0";
        if (numString(s) == 2) c = true;
        else if (numString(s) == 1) c = false;
        else return keep;
        string cde = s.substr(0, s.find(" ") + 1); // take the code
        s = s.substr(cde.length()); time T;
        if (c == false)
        {
            T = StoT(s);
        }
        else
        {
            string t = s.substr(0, s.find(" ") + 1);
            s = s.substr(t.length());
            t = t.substr(0, t.find(" ")); T = StoT(t);
        }
        if (c == true)
        {
            if (s == "0" || s == "1")
            {
                stringstream ss(s); bool x;
                ss >> x; // take the case
                //minDiff = TtoI((*(*this->Route.begin()).Trip.begin()).timeA) - TtoI(T);
                //keep = (*(*this->Route.begin()).Trip.begin()).LP;
                if (minDiff < 1) minDiff *= -1;
                for (DoublyLL<busRoute>::Iterator it = this->Route.begin(); it != this->Route.end(); it++)
                {
                    if ((*it).code == cde.substr(0, cde.find(" ")))
                    {
                        for (DoublyLL<busTrip>::Iterator ot = (*it).Trip.begin(); ot != (*it).Trip.end(); ot++)
                        {
                            int temp = TtoI((*ot).timeB) - TtoI(T);
                            if (temp < 0) temp *= -1;
                            if (temp <= minDiff && (*ot).CASE == x)
                            {
                                minDiff = TtoI((*ot).timeA) - TtoI(T);
                                keep = (*ot).LP;
                            }
                        }
                        if (keep == "/0") return "-1";
                        break;
                    }
                }
            }
        }
        else
        {
            for (DoublyLL<busRoute>::Iterator it = this->Route.begin(); it != this->Route.end(); it++)
            {
                if ((*it).code == cde.substr(0, cde.find(" ")))
                {
                    for (DoublyLL<busTrip>::Iterator ot = (*it).Trip.begin(); ot != (*it).Trip.end(); ot++)
                        {
                            int temp = TtoI((*ot).timeB) - TtoI(T);
                            if (temp < 0) temp *= -1;
                            if (temp <= minDiff)
                            {
                                if (temp == minDiff && (*ot).CASE == 0)
                                {
                                    minDiff = TtoI((*ot).timeB) - TtoI(T);
                                    keep = (*ot).LP;
                                }
                                else if (temp < minDiff)
                                {
                                    minDiff = TtoI((*ot).timeB) - TtoI(T);
                                    keep = (*ot).LP;
                                }
                            }
                        }
                    if (keep == "/0") return "-1";
                    break;
                }
            }
        }
        return keep;
    }
    int TtoI(time A)
    {
        return A.hour * 60 + A.minute;
    }
    int timeCmp(time X, time Y)
    {
        if (X.hour > Y.hour)
        {
            return 1;
        }
        else if (X.hour == Y.hour)
        {
            if (X.minute > Y.minute) return 1;
            else if (X.minute < Y.minute) return -1;
            else return 0;
        }
        else return -1;
    }
    time StoT(string& s)
    {
        time T;
        string h = s.substr(0, 2);
        s = s.substr(h.length());
        stringstream hh(h); hh >> T.hour;
        stringstream mm(s); mm >> T.minute;
        return T;
    }
    class busTrip
    {
    protected:
        string LP;
        bool CASE;
        time timeA;
        time timeB;
        friend class BusSystem;
    };
    class busRoute
    {
    protected:
        string code;
        DoublyLL <busTrip> Trip;
        friend class BusSystem;
    };
};

int main()
{
    BusSystem* bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;
    cout << bs->query("INS 50 50D1-23342 1234 5678") << endl;
    cout << bs->query("CS 50 2134") << endl;
    return 0;
}