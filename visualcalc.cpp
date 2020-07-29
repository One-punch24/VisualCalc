#include "VisualCalc.h"
#include "ui_VisualCalc.h"
#include <vector>

#include "Node.h"
#define constPi 3.1415926
#define constE  2.7182818

double calcVal = 0.0;
bool divTrig = false;
bool mulTrig = false;
bool addTrig = false;
bool subTrig = false;

std::vector<double> x_;
std::vector<double> y_;
bool x_enable, y_enable;



std::map<std::string, double> variables;


VisualCalc::VisualCalc(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::VisualCalc)
{
    ui->setupUi(this);
    ui->Val->setText(QString::number(calcVal));
    ui->Val1->setText(QString::number(calcVal));
    ui->Diff_Val->setText(QString::number(calcVal));
    ui->CalcRes->setText(QString::number(calcVal));


    QPushButton* numButtons[23];
    for (int i = 0; i < 10; ++i) {
        QString butname = "Button" + QString::number(i);
        numButtons[i] = VisualCalc::findChild<QPushButton*>(butname);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Dot, SIGNAL(released()), this, SLOT(NumPressed()));
    for (int i = 1; i <= 22; i++) {
        QString butname = "Opr" + QString::number(i);
        numButtons[i] = VisualCalc::findChild<QPushButton*>(butname);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(MathButtonPressed()));
    }

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->DEL, SIGNAL(released()), this, SLOT(DeleteButtonPressed()));
    connect(ui->AC, SIGNAL(released()), this, SLOT(ClearButtonPressed()));
    connect(ui->ConstPi, SIGNAL(released()), this, SLOT(ConstButtonPressed()));
    connect(ui->ConstE, SIGNAL(released()), this, SLOT(ConstButtonPressed()));
    connect(ui->Var, SIGNAL(released()), this, SLOT(VarButtonPressed()));
    

    connect(ui->OK, SIGNAL(released()), this, SLOT(IntegrationEqualButtonPressed()));
    connect(ui->Diff_btn, SIGNAL(released()), this, SLOT(DerivateEqualButtonPressed()));



    connect(ui->Stat_Add_Data, SIGNAL(released()), this, SLOT(StatAddData()));
    connect(ui->Stat_Analysis, SIGNAL(released()), this, SLOT(StatAnalysis()));
    connect(ui->Stat_Del_Data, SIGNAL(released()), this, SLOT(StatDelData()));

    // used to build Tree
    Tree = new ExprTree;

    initTable();
}

VisualCalc::~VisualCalc()
{
    delete ui;
}

void VisualCalc::NumPressed()
{
    QPushButton* button = (QPushButton*)sender();
    QString butVal = button->text();
    QString displayVal = ui->Val->text();
    if ((displayVal.toDouble() == 0.0))
    {
        if (!butVal.compare(".")) 
        {
            ui->Val->setText("0.");
            ui->Val1->setText("0.");
            ui->CalcRes->setText("0.");
            ui->Diff_Val->setText("0.");
        }
        else if (!ui->Val->text().compare("0."))
        {
            QString newVal = displayVal + butVal;
            double dblNewVal = newVal.toDouble();
            ui->Val->setText(newVal);
            ui->Val1->setText(newVal);
            ui->Diff_Val->setText(newVal);
            ui->CalcRes->setText(newVal);
        }
        else
        {
            ui->Val->setText(butVal);
            ui->Val1->setText(butVal);
            ui->CalcRes->setText(butVal);
            ui->Diff_Val->setText(butVal);

        }
    }
    else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Val->setText(newVal);
        ui->Val1->setText(newVal);
        ui->Diff_Val->setText(newVal);
        ui->CalcRes->setText(newVal);
    }
}


void VisualCalc::MathButtonPressed()
{
    QString displayVal = ui->Val->text();
    // construct Const node
    if (!displayVal.isEmpty() && !(this->Tree->getSizeofQ() == 0 && displayVal.toDouble() == 0))
    {
        Node* N;
        if (!displayVal.compare("Pi")) N = new ConstNode(constPi);
        else if (!displayVal.compare("e")) N = new ConstNode(constE);
        else N = new ConstNode(displayVal.toDouble());
        this->Tree->enQueue(N);
        ui->Expr->setText(this->Tree->renewExpr());
        ui->Expr1->setText(this->Tree->renewExpr());
        ui->CalcExpr->setText(this->Tree->renewExpr());
        ui->DiffExpr->setText(this->Tree->renewExpr());
    }

    
    QPushButton* button = (QPushButton*)sender();
    QString butVal = button->whatsThis();
    // Done.TODO: complete, and what to compare
    if (butVal == QString::fromStdString("x"))
    {
        Node* N1 = new VarNode("x"); 
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("+")) 
    {
        Node* N1 = new AddNode(nullptr, nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("-"))
    {
        Node* N1 = new SubNode(nullptr, nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("*"))
    {
        Node* N1 = new MutliplyNode(nullptr, nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("/"))
    {
        Node* N1 = new DivNode(nullptr, nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("sin"))
    {
        Node* N1 = new SinNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("cos"))
    {
        Node* N1 = new CosNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("tan"))
    {
        Node* N1 = new TanNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("arcsin"))
    {
        Node* N1 = new ArcSinNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("arccos"))
    {
        Node* N1 = new ArcCosNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("arctan"))
    {
        Node* N1 = new ArcTanNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("lg"))
    {
        Node* N1 = new LgNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("ln"))
    {
        Node* N1 = new LnNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("log"))
    {
        Node* N1 = new LogNode(nullptr, nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("abs"))
    {
        Node* N1 = new AbsNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("!"))
    {
        Node* N1 = new FactNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("^"))
    {
        Node* N1 = new PowerNode(nullptr, nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("times root"))
    {
        Node* N1 = new TimesRootNode(nullptr, nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("sqrt"))
    {
        Node* N1 = new SqrtNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("^3"))
    {
        Node* N1 = new CubeNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("^2"))
    {
        Node* N1 = new SquareNode(nullptr);
        this->Tree->enQueue(N1);
    }
    // unknown symbol treated as new variables
    else
    {
        Node* N1 = new VarNode(butVal.toStdString());
        this->Tree->enQueue(N1);
    }
    ui->Expr->setText(this->Tree->renewExpr());
    ui->Expr1->setText(this->Tree->renewExpr());
    ui->DiffExpr->setText(this->Tree->renewExpr());
    ui->CalcExpr->setText(this->Tree->renewExpr());

    
    ui->Val->setText("");
    ui->Val1->setText("");
    ui->Diff_Val->setText("");
    ui->CalcRes->setText("");
}
/************************************************************
*�˴������ظ��Ƚ����أ�����˼·һ�£�һ���ɰ���ȥ�Ĳ�ͬ�ļ��������
*��Ҫ��������������Ĵ����ֱ����󵼵ģ�������ֵİ���
*************************************************************/
void VisualCalc::IntegrationEqualButtonPressed() {
    double solution = 0.0;
    QString str_low, str_up;
    double low, up;
    QString displayVal = ui->Val->text();
    if (!displayVal.isEmpty())
    {
        Node* N;
        if (!displayVal.compare("Pi")) N = new ConstNode(constPi);
        else if (!displayVal.compare("e")) N = new ConstNode(constE);
        else N = new ConstNode(displayVal.toDouble());
        this->Tree->enQueue(N);
        ui->Expr->setText(this->Tree->renewExpr());
        ui->Expr1->setText(this->Tree->renewExpr());
        ui->DiffExpr->setText(this->Tree->renewExpr());
        ui->CalcExpr->setText(this->Tree->renewExpr());
        str_low =ui->Lower->text();
        str_up = ui->Upper->text();
        low = str_low.toDouble();
        up=str_up.toDouble();
        
    }

    // Evaluation 
    this->Tree->buildTree();
    // TODO: evaluate equation with variables
    // when x=0?
    try
    {
        solution = NumIntegrationRomberg(this->Tree,low,up);
    }
    catch (ARITHMETIC_EXCEPTION)
    {
        // ArithmeticE
    }
    catch (NUMBER_FORMAT_EXCEPTION)
    {
        // unknown var
    }
    catch (NULL_POINTER_EXCEPTION)
    {
        // illgel expression
    }
    catch (...)
    {
        // others
    }

    // used to test derivate toString function
    // Node* testD = this->Tree->derivate("x");
    // testD->toString();

    ui->CalcRes->setText(QString::number(solution));
    ui->Val1->setText(QString("READY"));
    ui->Diff_Val->setText(QString("READY"));
    ui->Val->setText(QString("READY"));
    this->Tree->clear();
}

void VisualCalc::DerivateEqualButtonPressed() {
    double solution = 0.0;
    QString str_point;
    double point;
    QString displayVal = ui->Val->text();
    if (!displayVal.isEmpty())
    {
        Node* N;
        if (!displayVal.compare("Pi")) N = new ConstNode(constPi);
        else if (!displayVal.compare("e")) N = new ConstNode(constE);
        else N = new ConstNode(displayVal.toDouble());
        this->Tree->enQueue(N);
        ui->Expr->setText(this->Tree->renewExpr());
        ui->Expr1->setText(this->Tree->renewExpr());
        ui->DiffExpr->setText(this->Tree->renewExpr());
        ui->CalcExpr->setText(this->Tree->renewExpr());
        str_point = ui->Diff_x0->text();
        point = str_point.toDouble();

    }

    // Evaluation 
    this->Tree->buildTree();
    // TODO: evaluate equation with variables
    // when x=0?
    try
    {
        solution = NumDiff(this->Tree, point);
    }
    catch (ARITHMETIC_EXCEPTION)
    {
        // ArithmeticE
    }
    catch (NUMBER_FORMAT_EXCEPTION)
    {
        // unknown var
    }
    catch (NULL_POINTER_EXCEPTION)
    {
        // illgel expression
    }
    catch (...)
    {
        // others
    }

    // used to test derivate toString function
    // Node* testD = this->Tree->derivate("x");
    // testD->toString();

    ui->CalcRes->setText(QString("READY"));
    ui->Val1->setText(QString("READY"));
    ui->Diff_Val->setText(QString::number(solution));
    ui->Val->setText(QString("READY"));
    this->Tree->clear();
}

void VisualCalc::EqualButtonPressed() {
    double solution = 0.0;

    QString displayVal = ui->Val->text();
    if (!displayVal.isEmpty()) 
    {
        Node* N;
        if (!displayVal.compare("Pi")) N = new ConstNode(constPi);
        else if (!displayVal.compare("e")) N = new ConstNode(constE);
        else N = new ConstNode(displayVal.toDouble());
        this->Tree->enQueue(N);
        ui->Expr->setText(this->Tree->renewExpr());
        ui->Expr1->setText(this->Tree->renewExpr());
        ui->DiffExpr->setText(this->Tree->renewExpr());
        ui->CalcExpr->setText(this->Tree->renewExpr());
    }
    
    // Evaluation 
    this->Tree->buildTree();
    // TODO: evaluate equation with variables
    // when x=0?
    try
    {
        solution = this->Tree->evaluate();
    }
    catch (ARITHMETIC_EXCEPTION)
    {
        // ArithmeticE
    }
    catch (NUMBER_FORMAT_EXCEPTION)
    {
        // unknown var
    }
    catch (NULL_POINTER_EXCEPTION)
    {
        // illgel expression
    }
    catch (...)
    {
        // others
    }

    // used to test derivate toString function
    // Node* testD = this->Tree->derivate("x");
    // testD->toString();

    ui->Val->setText(QString::number(solution));
    ui->Val1->setText(QString("READY"));
    ui->Diff_Val->setText(QString("READY"));
    ui->CalcRes->setText(QString("READY"));
    this->Tree->clear();
}

void VisualCalc::ChangeNumberSign()
{
    QString displayVal = ui->Val->text();
    QRegExp reg("[-+]?[0-9.]*");
    if (reg.exactMatch(displayVal))
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Val->setText(QString::number(dblDisplayValSign));
        ui->Val1->setText(QString::number(dblDisplayValSign));
        ui->Diff_Val->setText(QString::number(dblDisplayValSign));
        ui->CalcRes->setText(QString::number(dblDisplayValSign));
    }
}

void VisualCalc::DeleteButtonPressed()
{
    QString displayVal = ui->Val->text();
    if (displayVal.compare(""))
    {
        displayVal.chop(1);
        ui->Val->setText(displayVal);
        ui->Val1->setText(displayVal);
        ui->Diff_Val->setText(displayVal);
        ui->CalcRes->setText(displayVal);
    }
    else
    {
        this->Tree->del();
        ui->Expr->setText(this->Tree->renewExpr());
        ui->Expr1->setText(this->Tree->renewExpr());
        ui->DiffExpr->setText(this->Tree->renewExpr());
        ui->CalcExpr->setText(this->Tree->renewExpr());
    }

}

void VisualCalc::ClearButtonPressed()
{
    this->Tree->clear();
    ui->Val->setText("0");
    ui->Val1->setText("0");
    ui->Diff_Val->setText("0");
    ui->CalcRes->setText("0");
    ui->Upper->setText("");
    ui->Lower->setText("");
    ui->Diff_x0->setText("");

    ui->Expr->setText(this->Tree->renewExpr());
    ui->Expr1->setText(this->Tree->renewExpr());
    ui->DiffExpr->setText(this->Tree->renewExpr());
    ui->CalcExpr->setText(this->Tree->renewExpr());

}

void VisualCalc::ConstButtonPressed()
{
    QPushButton* button = (QPushButton*)sender();
    QString butVal = button->objectName();
    if (!butVal.compare("ConstPi"))
    {
        ui->Val->setText("Pi");
        ui->Val1->setText("Pi");
        ui->Diff_Val->setText("Pi");
        ui->CalcRes->setText("Pi");
    }
    if (!butVal.compare("ConstE"))
    {
        ui->Val->setText("e");
        ui->Val1->setText("e");
        ui->CalcRes->setText("e");
        ui->Diff_Val->setText("e");

    }
}

void VisualCalc::VarButtonPressed()
{
    this->Tree->setVar();
    QPushButton* button = (QPushButton*)sender();
    Node* N = new VarNode("x");
    this->Tree->enQueue(N);
    ui->Expr->setText(this->Tree->renewExpr());
    ui->Expr1->setText(this->Tree->renewExpr());
    ui->DiffExpr->setText(this->Tree->renewExpr());
    ui->CalcExpr->setText(this->Tree->renewExpr());
    ui->Diff_Val->setText("");
    ui->CalcRes->setText("");

}

void VisualCalc::on_Generate_clicked()
{
    QString displayVal = ui->Expr1->text();
    if (!displayVal.isEmpty())
    {
        new_graph = new Graph(nullptr, *this->Tree);
        new_graph->show();
    }

}

void VisualCalc::initTable()
{
    QTableWidgetItem* header;
    QStringList header_txt;
    header_txt << "    x    " << "    y    ";
    ui->Stat_Table_Widget->setHorizontalHeaderLabels(header_txt);
    ui->Stat_Table_Widget->setColumnCount(header_txt.count());
    for (int i = 0; i < ui->Stat_Table_Widget->columnCount(); i++)
    {
        header = new QTableWidgetItem(header_txt.at(i));
        QFont font = header->font();
        font.setBold(true);
        font.setPointSize(9);
        header->setFont(font);
        header->setBackground(QBrush(QColor(169, 204, 227)));
        ui->Stat_Table_Widget->setHorizontalHeaderItem(i, header);
    }
    ui->Stat_Table_Widget->setAlternatingRowColors(true);
    ui->Stat_Table_Widget->resizeColumnsToContents();
    ui->Stat_Table_Widget->resizeRowsToContents();
    ui->Stat_Table_Widget->verticalHeader()->setVisible(false);
}

void VisualCalc::StatAddData()
{
    int curRow = ui->Stat_Table_Widget->rowCount();
    ui->Stat_Table_Widget->insertRow(curRow);
    QTableWidgetItem* item = nullptr;
    for (int i = 0; i < 3; i++)
    {
        item = new QTableWidgetItem();
        ui->Stat_Table_Widget->setItem(curRow + 1, i, item);
    }
}

void VisualCalc::StatDelData()
{
    int curRow = ui->Stat_Table_Widget->currentRow();
    ui->Stat_Table_Widget->removeRow(curRow);
    
}

void VisualCalc::StatAnalysis()
{

    x_enable = y_enable = true;
    QTableWidgetItem* cellItem;
    for (int i = 0; i < ui->Stat_Table_Widget->rowCount(); i++)
    {
        cellItem = ui->Stat_Table_Widget->item(i, 0);
        if (cellItem) x_.push_back(cellItem->text().toDouble());
        else x_enable = false;
        cellItem = ui->Stat_Table_Widget->item(i, 1);
        if (cellItem) y_.push_back(cellItem->text().toDouble());
        else y_enable = false;
    }
    new_stat = new Stat;
    new_stat->show();
}

