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
