#include "stat.h"
#include "ui_stat.h"


extern std::vector<double> x_;
extern std::vector<double> y_;
extern bool x_enable, y_enable;


#include "statistic.h"

// ���ݸ���number
double stat_Number(vector<double> const x)
{
    return x.size();
}


// �����ܺ�sum
double stat_Sum(vector<double> const x)
{
    return accumulate(x.begin(), x.end(), 0.0);
}


// ƽ����Mean Value
double stat_MeanValue(vector<double> const x)
{

    if (x.size() == 0)
    {
    //          cout << "Error: Empty vector";
        exit(1);
    }

    return accumulate(x.begin(), x.end(), 0.0) / x.size();
}


// ����Variance
double stat_Variance(vector<double> const x)
{

    if (x.size() == 0)
    {
        //        cout<<"Error: Empty vector";
        exit(1);
    }

    double mean = stat_MeanValue(x);
    vector<double> diff(x.size());

    // transform (x.begin(), x.end(), diff.begin(), std::bind2nd(std::minus<double>(), mean));
    // lambda
    transform(x.begin(), x.end(), diff.begin(), [mean](double x) { return x - mean; });

    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);

    return sq_sum / x.size();
}


// ��׼ƫ��Standard Deviation
double stat_StandardDeviation(vector<double> const x)
{

    if (x.size() == 0)
    {
        //        cout<<"Error: Empty vector";
        exit(1);
    }

    double mean = stat_MeanValue(x);
    vector<double> diff(x.size());

    // transform (x.begin(), x.end(), diff.begin(), std::bind2nd(std::minus<double>(), mean));
    // lambda
    transform(x.begin(), x.end(), diff.begin(), [mean](double x) { return x - mean; });

    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);

    return sqrt(sq_sum / x.size());
}

// ��ֵMaxima and Minima
double stat_Maxima(vector<double> const x)
{

    if (x.size() == 0)
    {
        //        cout<<"Error: Empty vector";
        exit(1);
    }

    double max;
    for_each(x.begin(), x.end(), [&](int n) {
        max = (max > n) ? max : n;
        });
    return max;
}
double stat_Minima(vector<double> const x)
{

    if (x.size() == 0)
    {
        //        cout<<"Error: Empty vector";
        exit(1);
    }

    double min;
    for_each(x.begin(), x.end(), [&](int n) {
        min = (min < n) ? min : n;
        });
    return min;
}


// ��m/k��λ��Quantile
double stat_Quantile(vector<double> const x, int const k, int const m)
{

    if (x.size() == 0)
    {
        //       cout<<"Error: Empty vector";
        exit(1);
    }

    vector<double> y = x;
    nth_element(y.begin(), y.begin() + y.size() * m / k, y.end(), std::greater<int>());
    return y[y.size() * m / k];
}


// k �����ľ�kth-Central Moment
double stat_CentralMoment(vector<double> const x, int const k)
{

    if (x.size() == 0)
    {
        //        cout<<"Error: Empty vector";
        exit(1);
    }

    if (k == 1)
    {
        double m1 = 0;
        double m = stat_MeanValue(x);
        double num = x.size();
        double delta;
        for_each(x.begin(), x.end(), [&](int n) {
            delta = n - m;
            m1 += delta / num;
            });
        return m1;
    }
    else if (k == 2)
    {
        double m1 = 0, m2 = 0;
        double m = stat_MeanValue(x);
        double num = x.size();
        double a21 = (num - 1) / num;
        double delta, delta2;
        for_each(x.begin(), x.end(), [&](int n) {
            delta = n - m;
            delta2 = delta * delta;
            m2 += a21 * delta2;
            m1 += delta / num;
            });
        return m2;
    }
    else if (k == 3)
    {
        double m1 = 0, m2 = 0, m3 = 0;
        double m = stat_MeanValue(x);
        double num = x.size();
        double a21 = (num - 1) / num, a31 = a21 * (num - 2) / num, a32 = 3 / num;
        double delta, delta2, delta3;
        for_each(x.begin(), x.end(), [&](int n) {
            delta = n - m;
            delta2 = delta * delta;
            delta3 = delta2 * delta;
            m3 += a31 * delta3 - a32 * m2;
            m2 += a21 * delta2;
            m1 += delta / num;
            });
        return m3;
    }
    else if (k == 4)
    {
        double m1 = 0, m2 = 0, m3 = 0, m4 = 0;
        double m = stat_MeanValue(x);
        double num = x.size();
        double a21 = (num - 1) / num, a31 = a21 * (num - 2) / num, a32 = 3 / num, a43 = 4 / num,
            a42 = 6 / (num * num), a41 = a21 * (num * num - 3 * num + 3) / (num * num);
        double delta, delta2, delta3, delta4;
        for_each(x.begin(), x.end(), [&](int n) {
            delta = n - m;
            delta2 = delta * delta;
            delta3 = delta2 * delta;
            delta4 = delta3 * delta;
            m4 += a41 * delta4 + a42 * m2 - a43 * m3;
            m3 += a31 * delta3 - a32 * m2;
            m2 += a21 * delta2;
            m1 += delta / num;
            });
        return m4;
    }
    else
    {
        double var = 0;
        double m = stat_MeanValue(x);
        double delta;
        for_each(x.begin(), x.end(), [&](int n) {
            delta = n - m;
            var += pow(delta, k);
            });
        return var;
    }
}


// ����ƽ��Harmonic Mean
double stat_HarmonicMean(vector<double> const x)
{

    if (x.size() == 0)
    {
        //        cout<<"Error: Empty vector";
        exit(1);
    }

    double H1;
    for_each(x.begin(), x.end(), [&](int n) {
        H1 += 1 / n;
        });
    return 1 / H1;
}


//����ƽ��Geometric Mean
double stat_GeometricMean(vector<double> const x)
{

    if (x.size() == 0)
    {
        //        cout<<"Error: Empty vector";
        exit(1);
    }

    return pow(stat_Sum(x), 1 / (stat_Number(x)));
}


// ƫ��Skewness
double stat_Skewness(vector<double> const x)
{

    if (x.size() == 0)
    {
        //        cout<<"Error: Empty vector";
        exit(1);
    }

    double num = 0, num_old = 0, m = 0, m2 = 0, m3 = 0, m4 = 0;
    double delta, delta_n, delta_n2, term;
    for_each(x.begin(), x.end(), [&](int n) {
        num_old = n;
        num = num + 1;
        delta = n - m;
        delta_n = delta / num;
        delta_n2 = delta_n * delta_n;
        term = delta * delta_n * num_old;
        m += delta_n;
        m3 += term * delta_n * (num - 2) - 3 * delta_n * m2;
        m2 = m2 + term;
        });
    return sqrt(num) * m3 / (pow(m2, 3 / 2));
}


// ���Kurtosis
double stat_Kurtosis(vector<double> const x)
{
    if (x.size() == 0)
    {
        //        cout<<"Error: Empty vector";
        exit(1);
    }

    double num = 0, num_old = 0, m = 0, m2 = 0, m3 = 0, m4 = 0;
    double delta, delta_n, delta_n2, term;
    for_each(x.begin(), x.end(), [&](int n) {
        num_old = n;
        num = num + 1;
        delta = n - m;
        delta_n = delta / num;
        delta_n2 = delta_n * delta_n;
        term = delta * delta_n * num_old;
        m += delta_n;
        m4 += term * delta_n2 * (num * num - 3 * num + 3) + 6 * delta_n2 * m2 - 4 * delta_n * m3;
        m3 += term * delta_n * (num - 2) - 3 * delta_n * m2;
        m2 = m2 + term;
        });
    return num * m4 / (m2 * m2);
}


// ����ϵ��Coefficient of Variation
double stat_CoefficientOfVariance(vector<double> const x)
{
    if (x.size() == 0)
    {
        //        cout<<"Error: Empty vector";
        exit(1);
    }

    return stat_StandardDeviation(x) / stat_MeanValue(x);
}

// ���ϵ��Covariance
double stat_Covariance(vector<double> x, vector<double> y)
{
    if (x.size() == 0 || y.size() == 0)
    {
        //        cout<<"Error: 0 size";
        exit(1);
    }
    if (x.size() != y.size())
    {
        //        cout<<"Error: Unequal size";
        exit(2);
    }

    int num = x.size();
    double mx = stat_MeanValue(x), my = stat_MeanValue(y);
    double covariance = 0, dx, dy;
    for (int i = 0; i < num; i++)
    {
        dx = x[i] - mx;
        dy = y[i] - my;
        covariance += dx * dy / num;
    }

    return covariance;
}


// Regression

// ���������Իع�Simple Linear Regression
double stat_SimpleLinearRegression(vector<double> const x, vector<double> const y)
{
    if (x.size() == 0 || y.size() == 0)
    {
        //        cout<<"Error: 0 size";
        exit(1);
    }
    if (x.size() != y.size())
    {
        //        cout<<"Error: Unequal size";
        exit(2);
    }

    int num = x.size();
    double cross = 0;
    for (int i = 0; i < num; i++)
    {
        cross += x[i] * y[i];
    }
    double sx = stat_Sum(x), sy = stat_Sum(y), x2 = stat_CentralMoment(x, 2), y2 = stat_CentralMoment(y, 2),
        mx = stat_MeanValue(x), my = stat_MeanValue(y);
    double beta = (num * cross - sx * sy) / (num * x2 - sx * sx);
    double alpha = my - beta * mx;
    double r = (cross / num - mx * my) / sqrt((x2 / num - mx * mx) * (y2 / num - my * my));

    return r;
}

double stat_SimpleLinearRegression_alpha(vector<double> const x, vector<double> const y)
{
    if (x.size() == 0 || y.size() == 0)
    {
        //        cout<<"Error: 0 size";
        exit(1);
    }
    if (x.size() != y.size())
    {
        //        cout<<"Error: Unequal size";
        exit(2);
    }

    int num = x.size();
    double cross = 0;
    for (int i = 0; i < num; i++)
    {
        cross += x[i] * y[i];
    }
    double sx = stat_Sum(x), sy = stat_Sum(y), x2 = stat_CentralMoment(x, 2), y2 = stat_CentralMoment(y, 2),
        mx = stat_MeanValue(x), my = stat_MeanValue(y);
    double beta = (num * cross - sx * sy) / (num * x2 - sx * sx);
    double alpha = my - beta * mx;
    double r = (cross / num - mx * my) / sqrt((x2 / num - mx * mx) * (y2 / num - my * my));

    return alpha;
}

double stat_SimpleLinearRegression_beta(vector<double> const x, vector<double> const y)
{
    if (x.size() == 0 || y.size() == 0)
    {
        //        cout<<"Error: 0 size";
        exit(1);
    }
    if (x.size() != y.size())
    {
        //        cout<<"Error: Unequal size";
        exit(2);
    }

    int num = x.size();
    double cross = 0;
    for (int i = 0; i < num; i++)
    {
        cross += x[i] * y[i];
    }
    double sx = stat_Sum(x), sy = stat_Sum(y), x2 = stat_CentralMoment(x, 2), y2 = stat_CentralMoment(y, 2),
        mx = stat_MeanValue(x), my = stat_MeanValue(y);
    double beta = (num * cross - sx * sy) / (num * x2 - sx * sx);
    double alpha = my - beta * mx;
    double r = (cross / num - mx * my) / sqrt((x2 / num - mx * mx) * (y2 / num - my * my));

    return beta;
}


// Hypothesis Test

// t ����Student��s t-test
// ������
double stat_TTest(vector<double> const x, int const mux)
{
    return (stat_MeanValue(x) - mux) / sqrt(stat_StandardDeviation(x) / x.size());
}
// ˫����
double stat_TTest(vector<double> const x, vector<double> const y)
{
    return (stat_MeanValue(x) - stat_MeanValue(y)) / sqrt(stat_StandardDeviation(x) / x.size() + stat_StandardDeviation(y) / y.size());
}


// Ƥ��ɭ��������Pearson��s Chi-squared Test
double stat_ChiUniformTest(vector<double> const observed)
{
    int num = observed.size();
    double sum = 0, chisquare = 0;
    double expected;
    for_each(observed.begin(), observed.end(), [&](int n) {
        sum += n;
        expected = sum / num;
        chisquare += (n - expected) * (n - expected) / expected;
        });
    return chisquare;
}


Stat::Stat(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Stat)
{
    ui->setupUi(this);
    if (x_enable) {
        ui->lineEdit->setText(QString::number(stat_Sum(x_)));
        ui->lineEdit_2->setText(QString::number(stat_MeanValue(x_)));
        ui->lineEdit_7->setText(QString::number(stat_HarmonicMean(x_)));
        ui->lineEdit_8->setText(QString::number(stat_GeometricMean(x_)));
        ui->lineEdit_3->setText(QString::number(stat_Variance(x_)));
        ui->lineEdit_4->setText(QString::number(stat_StandardDeviation(x_)));
        ui->lineEdit_5->setText(QString::number(stat_Maxima(x_)));
        ui->lineEdit_6->setText(QString::number(stat_Minima(x_)));
        ui->lineEdit_9->setText(QString::number(stat_Skewness(x_)));
        ui->lineEdit_10->setText(QString::number(stat_Kurtosis(x_)));
        ui->lineEdit_11->setText(QString::number(stat_CoefficientOfVariance(x_)));
    }
    if (y_enable) {
        ui->lineEdit_16->setText(QString::number(stat_Sum(y_)));
        ui->lineEdit_15->setText(QString::number(stat_MeanValue(y_)));
        ui->lineEdit_21->setText(QString::number(stat_HarmonicMean(y_)));
        ui->lineEdit_25->setText(QString::number(stat_GeometricMean(y_)));
        ui->lineEdit_14->setText(QString::number(stat_Variance(y_)));
        ui->lineEdit_13->setText(QString::number(stat_StandardDeviation(y_)));
        ui->lineEdit_17->setText(QString::number(stat_Maxima(y_)));
        ui->lineEdit_18->setText(QString::number(stat_Minima(y_)));
        ui->lineEdit_28->setText(QString::number(stat_Skewness(y_)));
        ui->lineEdit_29->setText(QString::number(stat_Kurtosis(y_)));
        ui->lineEdit_30->setText(QString::number(stat_CoefficientOfVariance(y_)));
    }
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(ExecQuantile()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(ExecCM()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(ExecTT()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(ExecLinearA()));
}

Stat::~Stat()
{
    delete ui;
}


void Stat::ExecQuantile()
{
    int m = ui->lineEdit_19->text().toInt();
    int k = ui->lineEdit_20->text().toInt();
    if (m != 0 && k != 0)
    {
        if (x_enable) ui->lineEdit_22->setText(QString::number(stat_Quantile(x_, k, m)));
        if (y_enable) ui->lineEdit_23->setText(QString::number(stat_Quantile(y_, k, m)));
    }
}

void Stat::ExecCM()
{
    int k = ui->lineEdit_26->text().toInt();
    if (k != 0)
    {
        if (x_enable) ui->lineEdit_27->setText(QString::number(stat_CentralMoment(x_, k)));
        if (y_enable) ui->lineEdit_24->setText(QString::number(stat_CentralMoment(y_, k)));
    }
}

void Stat::ExecLinearA()
{
    if (x_enable && y_enable)
    {
        ui->lineEdit_33->setText(QString::number(stat_SimpleLinearRegression_alpha(x_, y_)));
        ui->lineEdit_31->setText(QString::number(stat_SimpleLinearRegression_beta(x_, y_)));
        ui->lineEdit_32->setText(QString::number(stat_SimpleLinearRegression(x_, y_)));
        ui->lineEdit_38->setText(QString::number(stat_Covariance(x_, y_)));
    }
}

void Stat::ExecTT()
{
    int mux = ui->lineEdit_34->text().toInt();
    if (mux != 0)
    {
        if (x_enable) ui->lineEdit_35->setText(QString::number(stat_TTest(x_, mux)));
        if (y_enable) ui->lineEdit_36->setText(QString::number(stat_TTest(y_, mux)));
    }
    if (x_enable && y_enable)        
    ui->lineEdit_37->setText(QString::number(stat_TTest(x_, y_)));

}