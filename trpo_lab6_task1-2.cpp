#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <memory>

using namespace std;

struct Transformer;

struct Number;
struct Variable;

struct BinaryOperation;
struct FunctionCall;

struct Expression {
    virtual ~Expression() {}
    virtual double evaluate() const = 0;
    virtual Expression* transform(class Transformer* tr) const = 0;
};


struct Transformer {
    virtual ~Transformer() {}
    virtual Expression* transformNumber(Number const*) = 0;
    virtual Expression* transformBinaryOperation(BinaryOperation const*) = 0;
    virtual Expression* transformFunctionCall(FunctionCall const*) = 0;
    virtual Expression* transformVariable(Variable const*) = 0;
};


struct Number : Expression {
    Number(double value) : value_(value) {}
    double value() const { return value_; }
    double evaluate() const override { return value_; }
    Expression* transform(Transformer* tr) const override { return tr->transformNumber(this); }
private:
    double value_;
};

struct Variable : Expression {
    Variable(string const& name) : name_(name) {}
    string const& name() const { return name_; }
    double evaluate() const override { return 0.0; }
    Expression* transform(Transformer* tr) const override { return tr->transformVariable(this); }
private:
    string const name_;
};


struct BinaryOperation : Expression {
    enum { PLUS = '+', MINUS = '-', DIV = '/', MUL = '*' };
    BinaryOperation(Expression const* left, int op, Expression const* right)
        : left_(left), op_(op), right_(right) {
        assert(left_ && right_);
    }
    ~BinaryOperation() { delete left_; delete right_; }
    Expression const* left() const { return left_; }
    Expression const* right() const { return right_; }
    int operation() const { return op_; }
    double evaluate() const override {
        double l = left_->evaluate(), r = right_->evaluate();
        switch (op_) {
        case PLUS: return l + r; case MINUS: return l - r;
        case DIV: return l / r; case MUL: return l * r;
        }
        return 0;
    }
    Expression* transform(Transformer* tr) const override { return tr->transformBinaryOperation(this); }
private:
    Expression const* left_;
    Expression const* right_;
    int op_;
};

struct FunctionCall : Expression {
    FunctionCall(string const& name, Expression const* arg)
        : name_(name), arg_(arg) {
        assert(arg_); assert(name_ == "sqrt" || name_ == "abs");
    }
    ~FunctionCall() { delete arg_; }
    string const& name() const { return name_; }
    Expression const* arg() const { return arg_; }
    double evaluate() const override {
        double val = arg_->evaluate();
        return (name_ == "sqrt") ? sqrt(val) : fabs(val);
    }
    Expression* transform(Transformer* tr) const override { return tr->transformFunctionCall(this); }
private:
    string const name_;
    Expression const* arg_;
};

