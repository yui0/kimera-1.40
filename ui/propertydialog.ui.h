/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <qapplication.h>
#include <qeventloop.h>
#include <qmessagebox.h>
#include <qregexp.h>
#include <qcolordialog.h>
#include <qpushbutton.h>
#include <qobject.h>
#include <qtooltip.h>
#include <qfiledialog.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qmessagebox.h>
#include "kimeraglobal.h"
#include "kanjiengine.h"
#include "config.h"
using namespace Kimera;

const int NUM_ROWS = 4;
const int NUM_COLS = 3;

static QString  ColorSetting[NUM_SETTING_TYPE][NUM_ROWS][NUM_COLS] = {
  { { "black",  "white", "1" },      // MSIME
    { "black",  "lightGray", "1" },
    { "black",  "white", "1" },
    { "white",  "blue",  "0" } },

  { { "blue",   "white", "0" },      // ATOK
    { "black",  "cyan",  "0" },
    { "blue",   "white", "0" },
    { "white",  "blue",  "0" } },

  { { "black",  "white", "1" },      // KINPUT2
    { "white",  "darkblue", "0" },
    { "black",  "white", "1" },
    { "white",  "darkblue", "0" } },

  { { "blue",   "gray",  "0" },      // VJE
    { "yellow", "black", "0" },
    { "yellow", "blue",  "0" },
    { "gray",   "blue",  "1" } },

  { { QString::null } },             // Current setting
};


void PropertyDialog::init()
{
  _kassign = new KeyAssigner(this, "key assigner");
  _colorsetting->setNumRows(NUM_ROWS);
  _colorsetting->setNumCols(NUM_COLS);

  for (int i = 0; i < _colorsetting->numRows(); ++i)
    _colorsetting->setRowStretchable (i ,TRUE);

  for (int i = 0; i < _colorsetting->numCols(); ++i)
    _colorsetting->setColumnStretchable(i ,TRUE);

  _cmbloadcolor->insertItem(tr("MS-IME風"), ST_MSIME);
  _cmbloadcolor->insertItem(tr("ATOK風"), ST_ATOK);
  _cmbloadcolor->insertItem(tr("Kinput2風"), ST_KINPUT2);
  _cmbloadcolor->insertItem(tr("VJE風"), ST_VJE);

  QStringList strlist;
  strlist << tr("なし") << tr("あり");
  for (int i = 0; i < NUM_ROWS; i++) {
    _colorsetting->setItem(i, 2, new QComboTableItem(_colorsetting, strlist));
  }

  QString tip = tr("日本語入力のオン／オフを切替えるキーを設定します。\n次回の起動から有効です。");
  QToolTip::add(_lblstartkey, tip);
  QToolTip::add(_cmbstartkey, tip);
  tip = tr("起動した直後の入力モードを選択します。");
  QToolTip::add(_lblinputmode, tip);
  QToolTip::add(_cmbinputmode, tip);
  tip = tr("起動した直後の入力方式を、ローマ字入力\nまたはかな入力から選択します。");
  QToolTip::add(_lblinputstyle, tip);
  QToolTip::add(_cmbinputstyle, tip);
  tip = tr("日本語入力がオフの時にツールバーを\n非表示にするか設定します。");
  QToolTip::add(_chkdispbar, tip);

  tip = tr("スペースキーを押した時に入力される\n空白の半角/全角を設定します。");
  QToolTip::add(_lblspacekey, tip);
  QToolTip::add(_cmbspacekey, tip);
  tip = tr("テンキーから入力した数字や\n記号の半角/全角を設定します。");
  QToolTip::add(_lbltenkey, tip);
  QToolTip::add(_cmbtenkey, tip);
  tip = tr("読点を選択します。");
  QToolTip::add(_lbltouten, tip);
  QToolTip::add(_cmbtouten, tip);
  tip = tr("句点を選択します。");
  QToolTip::add(_lblkuten, tip);
  QToolTip::add(_cmbkuten, tip);
  tip = tr("括弧を選択します。");
  QToolTip::add(_lblbracket, tip);
  QToolTip::add(_cmbbracket, tip);
  tip = tr("記号を選択します。");
  QToolTip::add(_lblsymbol, tip);
  QToolTip::add(_cmbsymbol, tip);
  QToolTip::add(_btnkeyassign, tr("キー設定ダイアログを表示します。"));

  QToolTip::add(_tab4, tr("これらの色設定はover-the-spot\nスタイルの場合に有効です。"));
  QToolTip::add(_cmbloadcolor, tr("リストから選択された色設定を読み込みます。"));
  QToolTip::add(_colorsetting, tr("個別に色を設定します。"));

  tip = tr("かな漢字変換エンジンを選択します。");
  QToolTip::add(_lblkanjisys, tip);
  QToolTip::add(_cmbkanjieng, tip);
  tip = tr("入力予測エンジンを選択します。");
  QToolTip::add(_lblpredict, tip);
  QToolTip::add(_cmbpredict, tip);
  tip = tr("かな漢字変換サーバのIPアドレス\nまたはホスト名を設定します。");
  QToolTip::add(_lblsvrname, tip);
  QToolTip::add(_edtsvrname, tip);
  tip = tr("接続するポート番号を設定します。");
  QToolTip::add(_lblport, tip);
  QToolTip::add(_edtport, tip);

  tip = tr("辞書ツールのコマンドを設定します");
  QToolTip::add(_grpcmd, tip);
  QToolTip::add(_cmbcmd, tip);

  _lblaboutkimera->setText(tr("<p align=\"center\"><font size=\"+3\"><i>Kimera</i></font><br>"
			      "Version " KIMERA_VERSION "</p>"
			      "<p align=\"center\">Copyright (c) 2003-2007  AOYAMA Kazz<br>"
			      "http://kimera.sourceforge.jp/</p>"
			      "<p align=\"center\">This program is distributed under the terms of "
			      "the GNU GENERAL PUBLIC LICENSE Version 2.</p>"));

  // Sets Kanji engine name
  QStringList englst = KanjiEngine::kanjiEngineList();
  for (QStringList::Iterator it = englst.begin(); it != englst.end(); ++it) {
    KanjiEngine* eng = KanjiEngine::kanjiEngine(*it);
    if ( eng ) {
      if ( eng->isKanjiConvEnabled() )
	_cmbkanjieng->insertItem(*it);

      if ( eng->isPredictionEnabled() )
	_cmbpredict->insertItem(*it);
    }
  }
}


void PropertyDialog::polish()
{
  loadSetting();
  QDialog::polish();
}


void PropertyDialog::loadSetting()
{
  _cmbstartkey->setCurrentText(Config::readEntry(_cmbstartkey->name(),
						 _cmbstartkey->currentText()));
  _cmbinputmode->setCurrentText(Config::readEntry(_cmbinputmode->name(),
						  _cmbinputmode->currentText()));
  _cmbinputstyle->setCurrentText(Config::readEntry(_cmbinputstyle->name(),
						   _cmbinputstyle->currentText()));
  _chkdispbar->setChecked(Config::readBoolEntry(_chkdispbar->name(), FALSE));

  _cmbspacekey->setCurrentText(Config::readEntry(_cmbspacekey->name(),
						 _cmbspacekey->currentText()));
  _cmbtenkey->setCurrentText(Config::readEntry(_cmbtenkey->name(),
					       _cmbtenkey->currentText()));
  _cmbkuten->setCurrentText(Config::readEntry(_cmbkuten->name(),
					      _cmbkuten->currentText()));
  _cmbtouten->setCurrentText(Config::readEntry(_cmbtouten->name(),
					       _cmbtouten->currentText()));
  _cmbsymbol->setCurrentText(Config::readEntry(_cmbsymbol->name(),
					       _cmbsymbol->currentText()));
  _cmbbracket->setCurrentText(Config::readEntry(_cmbbracket->name(),
						_cmbbracket->currentText()));

  _cmbkanjieng->setCurrentText(Config::readEntry(_cmbkanjieng->name(),
						 _cmbkanjieng->currentText()));
  slotKanjiEngineActivated(_cmbkanjieng->currentText());
  _grpremote->setChecked(Config::readBoolEntry(_grpremote->name(),
					       _grpremote->isChecked()));
  _edtsvrname->setText(Config::readEntry(_edtsvrname->name(), _edtsvrname->text()));
  _edtport->setText(Config::readEntry(_edtport->name(), _edtport->text()));
  _grppredict->setChecked(Config::readBoolEntry(_grppredict->name(),
						_grppredict->isChecked()));
  _cmbpredict->setCurrentText(Config::readEntry(_cmbpredict->name(),
						_cmbpredict->currentText()));

  _cmbcmd->setCurrentText(Config::readEntry(_cmbcmd->name(), ""));
  if (!_cmbcmd->currentText().isEmpty()) {
    int i;
    for (i = 0; i < _cmbcmd->count(); ++i)
      if (_cmbcmd->text(i) == _cmbcmd->currentText())
	break;

    if (i == _cmbcmd->count())
      _cmbcmd->insertItem(_cmbcmd->currentText(), 0);
  }

  int colorset = Config::readNumEntry(_cmbloadcolor->name(), ST_KINPUT2);
  if (colorset == ST_CURRENT_SETTING) {
    insertItemUserDefined();
  } else {
    removeItemUserDefined();
  }
  _cmbloadcolor->setCurrentItem(colorset);
  loadColorSetting( ST_CURRENT_SETTING );    // Loads color setting
}


bool PropertyDialog::saveSetting()
{
  // Check entry
  if (_grpremote->isEnabled() && _grpremote->isChecked()) {
    if (_edtsvrname->text().isEmpty() || _edtport->text().isEmpty()) {
      QMessageBox::warning(0, "Incorrect entry",
			   "Incorrect entry!\nInput Kanji server and port correctly.",
			   QMessageBox::Ok | QMessageBox::Default, 0);

      _tabwdg->showPage(_tab3);  // show page
      return FALSE;

    } else if ( !_edtport->text().contains(QRegExp("^[0-9]{4,5}$")) ) {
      QMessageBox::warning(0, "Incorrect port number",
			   "Incorrect port number!\nInput numerical string, 4 or 5 characters.",
			   QMessageBox::Ok | QMessageBox::Default, 0);

      _tabwdg->showPage(_tab3);  // show page
      return FALSE;
    }
  }

  // Saves setting
  bool restart = (_cmbstartkey->currentText() != Config::readEntry(_cmbstartkey->name(), tr("Zenkaku_Hankaku")));
  Config::writeEntry(_cmbstartkey->name(), _cmbstartkey->currentText());
  Config::writeEntry(_cmbinputmode->name(), _cmbinputmode->currentText());
  Config::writeEntry(_cmbinputstyle->name(), _cmbinputstyle->currentText());
  Config::writeEntry(_chkdispbar->name(), _chkdispbar->isChecked());

  Config::writeEntry(_cmbspacekey->name(), _cmbspacekey->currentText());
  Config::writeEntry(_cmbtenkey->name(), _cmbtenkey->currentText());
  Config::writeEntry(_cmbkuten->name(), _cmbkuten->currentText());
  Config::writeEntry(_cmbtouten->name(), _cmbtouten->currentText());
  Config::writeEntry(_cmbsymbol->name(), _cmbsymbol->currentText());
  Config::writeEntry(_cmbbracket->name(), _cmbbracket->currentText());

  Config::writeEntry(_cmbkanjieng->name(), _cmbkanjieng->currentText());
  Config::writeEntry(_grpremote->name(), _grpremote->isChecked());
  Config::writeEntry(_edtsvrname->name(), _edtsvrname->text());
  Config::writeEntry(_edtport->name(), _edtport->text());
  Config::writeEntry(_grppredict->name(), _grppredict->isChecked());
  Config::writeEntry(_cmbpredict->name(), _cmbpredict->currentText());

  Config::writeEntry(_cmbcmd->name(), _cmbcmd->currentText());

  Config::writeEntry(_cmbloadcolor->name(), _cmbloadcolor->currentItem());
  saveColorSetting();
  qDebug("Saved settings");

  if (restart) {
    QMessageBox::information(0, "Restart Kimera",
			     tr("設定を反映させるために Kimera の再起動が必要です。\n"
				"Kimera を再起動してください。"),
			     QMessageBox::Ok | QMessageBox::Default, 0);
  }

  emit settingChanged();
  return TRUE;
}


void PropertyDialog::changeColor( int row, int col, int, const QPoint &)
{
  if (col > 1)
    return;

  QColor color( white );
  if ( _colorsetting->text(row, col) ) {
    QColor c( _colorsetting->text(row, col) );
    if ( c.isValid() )
      color = c;    // default color
  }

  // Select color
  color = QColorDialog::getColor(color, this);
  if ( color.isValid() ) {
    QPixmap  pix = _colorsetting->pixmap( row, col );
    pix.resize(_colorsetting->columnWidth(col), _colorsetting->rowHeight(row));
    pix.fill( color );
    _colorsetting->setPixmap(row, col, pix);
    _colorsetting->setText(row, col, color.name());
    qDebug("get color name: %s", color.name().data());

    insertItemUserDefined();
  }
}

void PropertyDialog::execKeyAssiner()
{
  _kassign->show();
  _kassign->raise();
}


void PropertyDialog::loadColorSetting( int index )
{
  qApp->eventLoop()->processEvents(QEventLoop::ExcludeUserInput);

  int i, j;
  switch ( index ) {
  case ST_CURRENT_SETTING:         // Current setting
    // Loads Color table
    for (i = 0; i < NUM_ROWS; i++) {
      for (j = 0; j < NUM_COLS - 1; j++) {
        QColor color(Config::readEntry(QString(_colorsetting->name()) + "color"
                                       + QString::number(i * 2 + j), "white"));
        if ( color.isValid() ) {
          QPixmap  pix = _colorsetting->pixmap(i, j);
          pix.resize(_colorsetting->columnWidth(j), _colorsetting->rowHeight(i));
          pix.fill( color );
          _colorsetting->setPixmap(i, j, pix);
          _colorsetting->setText(i, j, color.name());
          qDebug("set color row: %d  col: %d  name: %s", i, j, color.name().data());
        }
      }

      QComboTableItem*  item = (QComboTableItem *)_colorsetting->item(i, j);
      QString  line = Config::readEntry(QString(_colorsetting->name()) + "underline" + QString::number(i), "0");
      item->setCurrentItem(line.toInt());
    }
    break;

  case ST_ATOK:
  case ST_KINPUT2:
  case ST_MSIME:
  case ST_VJE:
    // Loads Color table
    for (i = 0; i < NUM_ROWS; i++) {
      for (j = 0; j < NUM_COLS - 1; j++) {
        QColor color( ColorSetting[index][i][j] );
        if ( color.isValid() ) {
          QPixmap  pix = _colorsetting->pixmap(i, j);
          pix.resize(_colorsetting->columnWidth(j), _colorsetting->rowHeight(i));
          pix.fill( color );
          _colorsetting->setPixmap(i, j, pix);
          _colorsetting->setText(i, j, color.name());
          qDebug("set color row: %d  col: %d  name: %s", i, j, color.name().data());
        }
      }

      QComboTableItem*  item =  (QComboTableItem *)_colorsetting->item(i, j);
      item->setCurrentItem((ColorSetting[index][i][j]).toInt());
      qDebug("set color row: %d  col: %d  name: %s", i, j, (const char*)ColorSetting[index][i][j].local8Bit());
    }

    // Remove item user-defined
    if (Config::readNumEntry(_cmbloadcolor->name(), 0) != ST_CURRENT_SETTING) {
      removeItemUserDefined();
    }
    break;

  default:
    break;
  }
}


void PropertyDialog::saveColorSetting()
{
  // Saves color table items
  int i, j;
  for (i = 0; i < NUM_ROWS; i++) {
    for (j = 0; j < NUM_COLS - 1; j++) {
      if ( _colorsetting->text(i, j) ) {
	Config::writeEntry(QString(_colorsetting->name()) + "color" + QString::number(i * 2 + j),
			   _colorsetting->text(i, j) );
      }
    }

    int line = ((QComboTableItem*)_colorsetting->item(i, j))->currentItem();
    Config::writeEntry(QString(_colorsetting->name()) + "underline" + QString::number(i),
		       QString::number(line));
  }

  // Removes item, "User Definition".
  if (_cmbloadcolor->currentItem() != ST_CURRENT_SETTING)
    removeItemUserDefined();
}


void PropertyDialog::saveDefaultSetting()
{
  //Config::writeEntry("_cmbstartkey", tr("Zenkaku_Hankaku"), FALSE);
  Config::writeEntry("_cmbstartkey", tr("Kanji"), FALSE);
  Config::writeEntry("_cmbinputmode", tr("ひらがな"), FALSE);
  Config::writeEntry("_cmbinputstyle", tr("ローマ字入力"), FALSE);
  //Config::writeEntry("_chkdispbar", FALSE, FALSE);
  Config::writeEntry("_chkdispbar", TRUE, FALSE);

  Config::writeEntry("_cmbspacekey", tr("入力モードに従う"), FALSE);
  Config::writeEntry("_cmbtenkey", tr("入力モードに従う"), FALSE);
  Config::writeEntry("_cmbtouten", tr("、"), FALSE);
  Config::writeEntry("_cmbkuten", tr("。"), FALSE);
  Config::writeEntry("_cmbsymbol", tr("・"), FALSE);
  Config::writeEntry("_cmbbracket", tr("「」"), FALSE);

  Config::writeEntry("_cmbkanjieng", tr( DEFAULT_KANJIENGINE ), FALSE);
  Config::writeEntry("_grpremote", FALSE, FALSE);
  Config::writeEntry("_edtsvrname", QString::null, FALSE);
  Config::writeEntry("_edtport", QString::null, FALSE);
  Config::writeEntry("_grppredict", FALSE, FALSE);
  Config::writeEntry("_cmbpredict", tr("PRIME"), FALSE);

  Config::writeEntry("_cmbcmd", QString::null, FALSE);

  // Saves default color table items
  //const int setting = ST_KINPUT2;
  const int setting = ST_MSIME;
  Config::writeEntry("_cmbloadcolor", setting, FALSE);
  int i, j;
  for (i = 0; i < NUM_ROWS; i++) {
    for (j = 0; j < NUM_COLS - 1; j++) {
      Config::writeEntry(QString("_colorsetting") + "color" + QString::number(i * 2 + j),
			 ColorSetting[setting][i][j], FALSE);
    }

    Config::writeEntry(QString("_colorsetting") + "underline" + QString::number(i),
		       ColorSetting[setting][i][j], FALSE);
  }
}


void PropertyDialog::slotKanjiEngineActivated( const QString & string )
{
  KanjiEngine* eng = KanjiEngine::kanjiEngine(string);
  if (eng) {
    _grpremote->setEnabled(eng->isTCPConnectionSupported());
  } else {
    _grpremote->setEnabled(FALSE);
  }
}


void PropertyDialog::slotFileSelection()
{
  QFileInfo finf(_cmbcmd->currentText());
  QString dir = finf.exists() ? finf.dirPath() : QDir::homeDirPath();
  for (;;) {
    QString s = QFileDialog::getOpenFileName(dir, QString::null, this, "select file dialog",
				     "Select a file to execute");
    if (s.isEmpty())
      break;

    QFileInfo f(s);
    if (f.isExecutable()) {
      _cmbcmd->setCurrentText(s);
      break;
    } else {
      QMessageBox::warning(0, "File selection error",
			   tr("ファイルに実行権限がありません\n") + s);
      dir = f.dirPath();
    }
  }
}


void PropertyDialog::accept()
{
  if ( saveSetting() )
    QDialog::accept();
}


void PropertyDialog::insertItemUserDefined()
{
  if (_cmbloadcolor->count() == ST_CURRENT_SETTING)
    _cmbloadcolor->insertItem(tr("ユーザ定義"), ST_CURRENT_SETTING);
  _cmbloadcolor->setCurrentItem(ST_CURRENT_SETTING);
}


void PropertyDialog::removeItemUserDefined()
{
  if (_cmbloadcolor->count() == ST_CURRENT_SETTING + 1)
    _cmbloadcolor->removeItem(ST_CURRENT_SETTING);
}


void PropertyDialog::show()
{
  loadSetting();

  int x = Config::readNumEntry(QString("x_") + name(), (QApplication::desktop()->width() - width()) / 2);
  int y = Config::readNumEntry(QString("y_") + name(), (QApplication::desktop()->height() - height()) / 2);
  x = QMIN(QMAX(x, 0), QApplication::desktop()->width() - width());
  y = QMIN(QMAX(y, 0), QApplication::desktop()->height() - height());
  move(x, y);

  QDialog::show();
}


void PropertyDialog::hideEvent(QHideEvent* e)
{
  Config::writeEntry(QString("x_") + name(), x());
  Config::writeEntry(QString("y_") + name(), y());
  QDialog::hideEvent( e );
}
