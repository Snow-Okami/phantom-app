#include "main/utilities/include/utilities.h"

QString Utilities::Input()
{
    QTextStream cin(stdin);

    QString s = cin.readLine();

    return s;
}

const char * const Utilities::BoolToString(bool b)
{
  return b ? "true" : "false";
}

void Utilities::SetEnabledWidgetsInLayout(QLayout *layout, bool enabled)
{
   if (layout == NULL)
      return;

   QWidget *pw = layout->parentWidget();
   if (pw == NULL)
      return;

   foreach(QWidget *w, pw->findChildren<QWidget*>())
   {
      if (Utilities::IsChildWidgetOfAnyLayout(layout,w))
         w->setEnabled(enabled);
   }
}

bool Utilities::IsChildWidgetOfAnyLayout(QLayout *layout, QWidget *widget)
{
   if (layout == NULL or widget == NULL)
      return false;

   if (layout->indexOf(widget) >= 0)
      return true;

   foreach(QObject *o, layout->children())
   {
      if (Utilities::IsChildWidgetOfAnyLayout((QLayout*)o,widget))
         return true;
   }

   return false;
}

std::string Utilities::ParseCommand(QString str, QString delim, std::string &command)
{
    std::string s = QStringToString(str);
    std::string delimiter = QStringToString(delim);

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());
        break;
    }
    std::cout << "Token: " << token << " Returning: " << s << std::endl;
    command = token;
    return s;
}

std::vector<std::pair<std::string, std::string>> Utilities::ParseArguments(QString str, QString argDelim, QString valueDelim)
{
    //Convert Delimiters to regular strings
    std::string s = QStringToString(str);
    std::string ad = QStringToString(argDelim);
    std::string vd = QStringToString(valueDelim);
    //Create a list of key value pairs to store the arguements
    std::vector<std::pair<std::string, std::string>> arguments;
    //Initialize some needed vars
    //Prevent these while loops from going on infinitely if fed a malformed string
    int counter = 0;
    int infinitePrevention = 20;
    size_t pos, pos2 = 0;
    std::string token, name, value;
    //While we have another arguement to parse and after we hit the last arguement...
    while ((pos = s.find(ad)) != std::string::npos || s.length() > 0) {
        //Cut to the position of the first argument delimiter (separator)
        token = s.substr(0, pos);
        //While we have an arguement with a key value pair
        while((pos2 = token.find(vd)) != std::string::npos) {
            //Get name (key)
            name = token.substr(0, pos2);
            //Get value (starting from position AFTER the delimiter)
            value = token.substr(pos2 + vd.length(), token.length());
            //Form key value pair
            std::pair<std::string, std::string> pair (name, value);
            //Push it to our vector
            arguments.push_back(pair);
            //Erase the token as well as the delimiter
            token.erase(0, pos2 + vd.length());
            //Prevent while loops from going on forever
            if(counter > infinitePrevention) break;
            counter++;
        }
        //If we are on our last iteration - the last argument erase everything as we are done
        //This also prevents the first while loop from iterating again
        if(s.find(ad) == std::string::npos)
            s.erase(0, s.length());
        else //Normally delete up until the current delimiter
            s.erase(0, pos + ad.length());
        //Prevent while loops from going on forever
        if(counter > infinitePrevention) break;
        counter++;
    }
    return arguments;
}

void Utilities::DumpArgumentsToConsole(std::vector<std::pair<std::string, std::string>> arguments)
{
    //Iterate over arguments
    for(int i = 0; i < arguments.size(); i++)
    {
        std::cout << "PairName: " << arguments[i].first << " PairValue: " << arguments[i].second << std::endl;
    }
}

std::string Utilities::QStringToString(QString str)
{
    return str.toStdString();
}

QString Utilities::StringToQString(std::string str)
{
    return QString::fromStdString(str);

}

QString Utilities::StringToQString(const char * str)
{
    return QString::fromUtf8(str);
}

bool Utilities::StringToBoolean(std::string str)
{
    if(str == "True" || str == "true" || str == "1") return true;
    if(str == "False" || str == "false" || str == "0") return false;
    return false;
}

bool Utilities::QStringToBoolean(QString str)
{
    if(str == "True" || str == "true" || str == "1") return true;
    if(str == "False" || str == "false" || str == "0") return false;
    return false;
}
