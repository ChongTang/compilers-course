/* File: ast_expr.h
 * ----------------
 * The Expr class and its subclasses are used to represent
 * expressions in the parse tree.  For each expression in the
 * language (add, call, New, etc.) there is a corresponding
 * node class for that construct. 
 */


#ifndef _H_ast_expr
#define _H_ast_expr

#include "ast.h"
#include "ast_stmt.h"
#include "list.h"

class NamedType; // for new
class Type; // for NewArray
class FnDecl;
class ClassDecl;

class Expr : public Stmt 
{
  public:
    Expr(yyltype loc) : Stmt(loc) {}
    Expr() : Stmt() {}

    virtual Type* GetType() = 0;

  protected:
    ClassDecl* GetClassDecl(Scope *s);
    Decl* GetFieldDecl(Identifier *field, Type *base);
    Decl* GetFieldDecl(Identifier *field, Scope *scope);
};

/* This node type is used for those places where an expression is optional.
 * We could use a NULL pointer, but then it adds a lot of checking for
 * NULL. By using a valid, but no-op, node, we save that trouble */
class EmptyExpr : public Expr
{
  public:
//    const char *GetPrintNameForNode() { return "Empty"; }
    Type* GetType();
    void Check() {}
};

class IntConstant : public Expr 
{
  protected:
    int value;
  
  public:
    IntConstant(yyltype loc, int val);
//    const char *GetPrintNameForNode() { return "IntConstant"; }
//    void PrintChildren(int indentLevel);
    Type* GetType();
    void Check() {}
};

class DoubleConstant : public Expr 
{
  protected:
    double value;
    
  public:
    DoubleConstant(yyltype loc, double val);
//    const char *GetPrintNameForNode() { return "DoubleConstant"; }
//    void PrintChildren(int indentLevel);
    Type* GetType();
    void Check() {}
};

class BoolConstant : public Expr 
{
  protected:
    bool value;
    
  public:
    BoolConstant(yyltype loc, bool val);
//    const char *GetPrintNameForNode() { return "BoolConstant"; }
//    void PrintChildren(int indentLevel);
    Type* GetType();
    void Check() {}
};

class StringConstant : public Expr 
{ 
  protected:
    char *value;
    
  public:
    StringConstant(yyltype loc, const char *val);
//    const char *GetPrintNameForNode() { return "StringConstant"; }
//    void PrintChildren(int indentLevel);
    Type* GetType();
    void Check() {}
};

class NullConstant: public Expr 
{
  public: 
    NullConstant(yyltype loc) : Expr(loc) {}
//    const char *GetPrintNameForNode() { return "NullConstant"; }
    Type* GetType();
    void Check() {}
};

class Operator : public Node 
{
  protected:
    char tokenString[4];
    
  public:
    Operator(yyltype loc, const char *tok);
	friend std::ostream& operator<<(std::ostream& out, Operator *o) { return out << o->tokenString; }
//    const char *GetPrintNameForNode() { return "Operator"; }
//    void PrintChildren(int indentLevel);
 };
 
class CompoundExpr : public Expr
{
  protected:
    Operator *op;
    Expr *left, *right; // left will be NULL if unary
    
  public:
    CompoundExpr(Expr *lhs, Operator *op, Expr *rhs); // for binary
    CompoundExpr(Operator *op, Expr *rhs);             // for unary
//    void PrintChildren(int indentLevel);
	CompoundExpr(Expr *lhs, Operator *op);
	virtual void BuildScope(Scope *parent);
    virtual void Check();
};

class ArithmeticExpr : public CompoundExpr 
{
  public:
    ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
//    const char *GetPrintNameForNode() { return "ArithmeticExpr"; }
    Type* GetType();
    void Check();
};

class RelationalExpr : public CompoundExpr 
{
  public:
    RelationalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
//    const char *GetPrintNameForNode() { return "RelationalExpr"; }
    Type* GetType();
    void Check();
};

class EqualityExpr : public CompoundExpr 
{
  public:
    EqualityExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    const char *GetPrintNameForNode() { return "EqualityExpr"; }
    Type* GetType();
    void Check();
};

class LogicalExpr : public CompoundExpr 
{
  public:
    LogicalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    LogicalExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
    const char *GetPrintNameForNode() { return "LogicalExpr"; }
    Type* GetType();
    void Check();
};

class AssignExpr : public CompoundExpr 
{
  public:
    AssignExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    const char *GetPrintNameForNode() { return "AssignExpr"; }
    Type* GetType();
    void Check();
};

class LValue : public Expr 
{
  public:
    LValue(yyltype loc) : Expr(loc) {}
};

class This : public Expr 
{
  public:
    This(yyltype loc) : Expr(loc) {}
//    const char *GetPrintNameForNode() { return "This"; }
    Type* GetType();
    void Check();
};

class ArrayAccess : public LValue 
{
  protected:
    Expr *base, *subscript;
    
  public:
    ArrayAccess(yyltype loc, Expr *base, Expr *subscript);
//    const char *GetPrintNameForNode() { return "ArrayAccess"; }
//    void PrintChildren(int indentLevel);
    Type* GetType();
    void BuildScope(Scope *parent);
    void Check();
};

/* Note that field access is used both for qualified names
 * base.field and just field without qualification. We don't
 * know for sure whether there is an implicit "this." in
 * front until later on, so we use one node type for either
 * and sort it out later. */
class FieldAccess : public LValue 
{
  protected:
    Expr *base;	// will be NULL if no explicit base
    Identifier *field;
    
  public:
    FieldAccess(Expr *base, Identifier *field); //ok to pass NULL base
//    const char *GetPrintNameForNode() { return "FieldAccess"; }
//    void PrintChildren(int indentLevel);
    Type* GetType();
    void BuildScope(Scope *parent);
    void Check();
};

/* Like field access, call is used both for qualified base.field()
 * and unqualified field().  We won't figure out until later
 * whether we need implicit "this." so we use one node type for either
 * and sort it out later. */
class Call : public Expr 
{
  protected:
    Expr *base;	// will be NULL if no explicit base
    Identifier *field;
    List<Expr*> *actuals;
    
  public:
    Call(yyltype loc, Expr *base, Identifier *field, List<Expr*> *args);
//    const char *GetPrintNameForNode() { return "Call"; }
//    void PrintChildren(int indentLevel);
    Type* GetType();
    void BuildScope(Scope *parent);
    void Check();

  private:
    void CheckActuals(Decl *d);
};

class NewExpr : public Expr
{
  protected:
    NamedType *cType;
    
  public:
    NewExpr(yyltype loc, NamedType *clsType);
//    const char *GetPrintNameForNode() { return "NewExpr"; }
//    void PrintChildren(int indentLevel);
    Type* GetType();
    void Check();
};

class NewArrayExpr : public Expr
{
  protected:
    Expr *size;
    Type *elemType;
    
  public:
    NewArrayExpr(yyltype loc, Expr *sizeExpr, Type *elemType);
//    const char *GetPrintNameForNode() { return "NewArrayExpr"; }
//    void PrintChildren(int indentLevel);
    Type* GetType();
    void BuildScope(Scope *parent);
    void Check();
};

class ReadIntegerExpr : public Expr
{
  public:
    ReadIntegerExpr(yyltype loc) : Expr(loc) {}
//    const char *GetPrintNameForNode() { return "ReadIntegerExpr"; }
    Type* GetType();
    void Check() {}
};

class ReadLineExpr : public Expr
{
  public:
    ReadLineExpr(yyltype loc) : Expr (loc) {}
//    const char *GetPrintNameForNode() { return "ReadLineExpr"; }
	Type* GetType();
    void Check() {}
};

class PostfixExpr : public Expr
{
   protected:
     LValue *lvalue;
     Operator *op;
  public: 
    PostfixExpr(LValue *lv, Operator *op);
//    const char *GetPrintNameForNode() { return "PostfixExpr"; }
//    void PrintChildren(int indentLevel);
	Type* GetType();
    void Check() {}
};
    
#endif
