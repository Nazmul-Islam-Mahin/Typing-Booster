#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
using namespace std;

int length;
int result;
int wrong;

void selection(string &sen);
void accuracy(string &a, string &b, int &err, int &crr, float &ac);
void PrintResult(float time, float net, float gross, float ac, int err, string sentence, int ts);
bool option_check(char opt);
void time_sentence();

int main() {
    cout << endl << endl << endl << "\t\t\t\t\t************ WELCOME TO TYPE MASTER ************" << endl << endl;

    while (true) {
        string sen;
        selection(sen);

        if (wrong == 0) {
            string sentence;
            length = sen.size();
            time_t starttime;
            time_t endtime;

            cout << endl << endl << endl << "\t\t_(Enter_This_Text)_" << endl;
            cout << endl << "Type:- " << sen << endl;
            cout << endl << "Press and Type..." << endl;

            time(&starttime);
            getline(cin, sentence);
            time(&endtime);

            float words = ((float)sentence.size() / 5);
            float time = ((float)(endtime - starttime)) / 60;
            int tsec = (endtime - starttime);
            float acc = 0;
            int err = 0;
            int crr = 0;

            accuracy(sentence, sen, err, crr, acc);
            result = length - crr;
            float gross_wpm = (words / time);
            float net_wpm = gross_wpm - (((float)err / 5) / time);
            if (net_wpm < 1) {
                net_wpm = 0;
            }
            PrintResult(time, net_wpm, gross_wpm, acc, result, sentence, tsec);
        }

        cout << endl << endl << "Do You Want To Test Again ?" << endl << endl << "Type 'Y' for YES or 'N' for NO" << endl << endl;
        char opt;
        cin >> opt;
        cin.ignore();

        if (!option_check(opt)) {
            break;
        }
    }

    return 0;
}

void selection(string &sen) {
    wrong = 0;
    cout << endl << "Select Mode:" << endl;
    cout << "For Random Words (Type:- words)" << endl;
    cout << "For quote (Type:- quote)" << endl;
    cout << "For custom (Type:- custom)" << endl;
    string select;
    getline(cin, select);

    if (select == "words" || select == "words ") {
        cout << endl << "Select No. Of Words:" << endl;
        cout << "Type:- 10, 25 or 50" << endl;
        getline(cin, select);

        if (select == "10") {
            sen = "work school show these feel such need before eye early";
        } else if (select == "25") {
            sen = "hand now between plan can stand you while increase tell lead down "
                  "must real own facts because person might then this plan end "
                  "interest while";
        } else if (select == "50") {
            sen = "interest right in real during by begin leave write could all "
                  "program line very those hold part down first turn still the on "
                  "there will say another get would house leave day write after will "
                  "so life present as we need say new feel how person call may each find";
        } else {
            wrong++;
            cout << endl << "!Invalid, Enter a valid choice..." << endl;
            return;
        }
    } else if (select == "quote" || select == "quote ") {
        cout << endl << "Select quote size:" << endl;
        cout << "Type:- short, medium or long" << endl;
        getline(cin, select);

        if (select == "short") {
            sen = "The past is history, future is a mystery, now is a gift, "
                  "They call it the present...";
        } else if (select == "medium") {
            sen = "Not only do we come into fairly regular contact with people who "
                  "want to know what our family looks like, but we also navigate\n "
                  "a vast array of organizations and agencies that have their own "
                  "definitions of family and may, at times, impose them on us...";
        } else if (select == "long") {
            sen = "The road may be long, tortuous and wearied."
                  " But the resulting success is enduring, sure and sweet."
                  " The fool abandons hope in the wearied journey of life."
                  " The wise gets going - holding firmly to the promise of a better tomorrow."
                  " He that gives up too soon fails to understand that life rewards with"
                  " success only those who cling on to hope against hope."
                  " Those who hope when it is unfashionable to hope.";
        } else {
            wrong++;
            cout << endl << "!Invalid, Enter a valid choice..." << endl;
            return;
        }
    } else if (select == "custom" || select == "custom ") {
        cout << endl << "Enter The Text That You Wanna Type:" << endl;
        getline(cin, sen);
    } else {
        wrong++;
        cout << endl << "!Invalid, Enter a valid choice..." << endl;
        return;
    }
}

void accuracy(string &a, string &b, int &err, int &crr, float &ac) {
    int w = 0;
    int u = 0;
    string x = " ";

    while (u < b.size()) {
        while (a[w] == x[0]) {
            if (a[w] == b[u]) {
                crr++;
                u++;
            } else {
                err++;
            }
            w++;
        }

        if (w >= a.size()) {
            break;
        }

        while (b[u] == x[0]) {
            if (b[u] == a[w]) {
                crr++;
                w++;
            } else {
                err++;
            }
            u++;
        }

        while (b[u] != x[0]) {
            if (u >= b.size()) {
                break;
            }

            if (a[w] != x[0]) {
                if (b[u] == a[w]) {
                    crr++;
                } else {
                    err++;
                }

                u++;
                w++;
            } else if (a[w] == x[0]) {
                while (b[u] != x[0]) {
                    u++;
                    err++;
                    if (u >= b.size()) {
                        break;
                    }
                }
            }
        }

        if (u >= b.size()) {
            while (w < a.size()) {
                err++;
                w++;
            }
            break;
        } else if (w >= a.size()) {
            break;
        }

        if (a[w] == x[0]) {
            crr++;
        }

        while (a[w] != x[0]) {
            if (w >= a.size()) {
                while (u < b.size()) {
                    err++;
                    u++;
                }
                break;
            }
            err++;
            w++;
        }

        u++;
        w++;
    }

    ac = (float(crr) / float(b.size())) * 100;
}

void PrintResult(float time, float net, float gross, float ac, int err, string sentence, int ts) {
    cout << endl << endl << endl << "\t\t___________________ Result _____________________" << endl;
    cout.precision(2);
    cout << fixed;
    cout << endl << "\t\tGROSS SPEED" << "\t\t\t\tACCURACY" << endl;
    cout << "\t\t" << gross << " Wpm " << "\t\t\t\t" << ac << "%" << endl;
    cout << endl << "\t\tAVERAGE SPEED" << "\t\t\t\tTIME" << endl;
    cout << "\t\t" << net << " Wpm ";
    if (ts > 59) {
        cout << "\t\t\t\t" << time << " min" << endl << endl;
    } else {
        cout << "\t\t\t\t" << ts << " sec" << endl << endl;
    }
    cout << "\t\tKEYSTROKES" << "\t\t\t\tERRORS" << endl;
    cout << "\t\t" << sentence.size() << " Char " << "\t\t\t\t" << err << " Err" << endl;
    cout << "\t\t__" << endl << endl << endl;
}

bool option_check(char opt) {
    if (opt == 'Y' || opt == 'y') {
        return true;
    } else if (opt == 'N' || opt == 'n') {
        return false;
    } else {
        cout << endl << "Invalid choice! Please Try Again " << endl;
        char ch;
        cin >> ch;
        cin.ignore();
        return option_check(ch);
    }
}

void time_sentence() {
    string sentence;
    time_t starttime;
    time_t endtime;

    string sen = "Sample text for typing test.";
    cout << "Type this text:" << endl;
    cout << sen << endl;
    cout << "Press and type..." << endl;

    time(&starttime);
    getline(cin, sentence);
    time(&endtime);

    float timeTaken = ((float)(endtime - starttime)) / 60;
    float words = ((float)sentence.size() / 5);
    float gross_wpm = (words / timeTaken);
    int tsec = (endtime - starttime);
    float net_wpm = gross_wpm;

    cout << "Time taken: " << tsec << " seconds" << endl;
    cout << "Gross WPM: " << gross_wpm << endl;
}

