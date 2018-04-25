/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "highlighter.h"

Highlighter::Highlighter( QTextDocument * parent, int iLangType )
    : QSyntaxHighlighter(parent),
      _iLangType(iLangType)
{
    HighlightingRule rule;

    _keywordFormat.setForeground( Qt::blue );
    //keywordFormat.setFontWeight( QFont::Bold );
    QStringList keywordPatterns;

    if ( iLangType == 0 ) { // C
        keywordPatterns << "\\bchar\\b" << "\\bconst\\b" << "\\bauto\\b"
                        << "\\bif\\b" << "\\bwhile\\b" << "\\bdo\\b"
                        << "\\bfor\\b" << "\\bcontinue\\b" << "\\bbreak\\b"
                        << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                        << "\\binline\\b" << "\\bint\\b" << "\\bcase\\b"
                        << "\\blong\\b"  << "\\belse\\b"  << "\\bextern\\b"
                        << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                        << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                        << "\\btypedef\\b" << "\\bdefault\\b" << "\\bgoto\\b"
                        << "\\bunion\\b" << "\\bunsigned\\b" << "\\bregister\\b"
                        << "\\bsizeof\\b" << "\\bfloat\\b" << "\\bswitch\\b"
                        << "\\bvoid\\b" << "\\bvolatile\\b" << "\\breturn\\b"
                        << "\\basm\\b";
    }
    else if ( iLangType == 1 ) { // C++
        keywordPatterns << "\\balignas\\b" << "\\balignof\\b" << "\\band\\b"
                        << "\\band_eq\\b" << "\\basm\\b" << "\\bauto\\b"
                        << "\\bbitand\\b" << "\\bbitor\\b" << "\\bbool\\b" << "\\bbyte\\b"
                        << "\\bbreak\\b" << "\\bcase\\b" << "\\bcatch\\b"
                        << "\\bchar\\b" << "\\bchar16_t\\b" << "\\bchar32_t\\b"
                        << "\\bclass\\b" << "\\bcompl\\b" << "\\bconst\\b"
                        << "\\bconstexpr\\b" << "\\bconst_cast\\b" << "\\bcontinue\\b"
                        << "\\bdecltype\\b" << "\\bdefault\\b" << "\\bdelete\\b"
                        << "\\bdo\\b" << "\\bdouble\\b" << "\\bdynamic_cast\\b"
                        << "\\belse\\b" << "\\benum\\b" << "\\bexplicit\\b"
                        << "\\bexport\\b" << "\\bextern\\b" << "\\bfalse\\b"
                        << "\\bfloat\\b" << "\\bfor\\b" << "\\bforeach\\b" << "\\bfriend\\b"
                        << "\\bgoto\\b" << "\\bif\\b" << "\\binline\\b"
                        << "\\bint\\b" << "\\blong\\b" << "\\bmutable\\b"
                        << "\\bnamespace\\b" << "\\bnew\\b" << "\\bnoexcept\\b"
                        << "\\bnot\\b" << "\\bnot_eq\\b" << "\\bnullptr\\b"
                        << "\\boperator\\b" << "\\bor\\b" << "\\bor_eq\\b"
                        << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                        << "\\bregister\\b" << "\\breinterpret_cast\\b" << "\\breturn\\b"
                        << "\\bshort\\b" << "\\bsigned\\b" << "\\bsizeof\\b"
                        << "\\bstatic\\b" << "\\bstatic_cast\\b" << "\\bstruct\\b"
                        << "\\bswitch\\b" << "\\btemplate\\b" << "\\bthis\\b"
                        << "\\bthread_local\\b" << "\\bthrow\\b" << "\\btrue\\b"
                        << "\\btry\\b" << "\\btypedef\\b" << "\\btypeid\\b"
                        << "\\btypename\\b" << "\\bunion\\b" << "\\bunsigned\\b"
                        << "\\busing\\b" << "\\bvirtual\\b" << "\\bvoid\\b"
                        << "\\bvolatile\\b" << "\\bwchar_t\\b" << "\\bwhile\\b"
                        << "\\bxor\\b" << "\\bxor_eq\\b" << "\\boverride\\b"
                        << "\\bfinal\\b" << "\\bslots\\b" << "\\bsignal\\b";
    }
    else if ( iLangType == 2 ) { // Java
        keywordPatterns << "\\babstract\\b" << "\\bassert\\b" << "\\bboolean\\b"
                        << "\\bbreak\\b" << "\\bbyte\\b" << "\\bcase\\b"
                        << "\\bcatch\\b" << "\\bchar\\b" << "\\bclass\\b"
                        << "\\bconst\\b" << "\\bcontinue\\b" << "\\bdefault\\b"
                        << "\\bdo\\b" << "\\bdouble\\b" << "\\belse\\b"
                        << "\\benum\\b" << "\\bextends\\b" << "\\bfinal\\b"
                        << "\\bfinally\\b" << "\\bfloat\\b" << "\\bfor\\b"
                        << "\\bgoto\\b" << "\\bif\\b" << "\\bimplements\\b"
                        << "\\bimport\\b" << "\\binstanceof\\b" << "\\bint\\b"
                        << "\\binterface\\b" << "\\blong\\b" << "\\bnative\\b"
                        << "\\bnew\\b" << "\\bpackage\\b" << "\\bprivate\\b"
                        << "\\bprotected\\b" << "\\bpublic\\b" << "\\breturn\\b"
                        << "\\bshort\\b" << "\\bstatic\\b" << "\\bstrictfp\\b"
                        << "\\bsuper\\b" << "\\bswitch\\b" << "\\bsynchronized\\b"
                        << "\\bthis\\b" << "\\bthrow\\b" << "\\bthrows\\b"
                        << "\\btransient\\b" << "\\btry\\b" << "\\bvoid\\b"
                        << "\\bvolatile\\b" << "\\bwhile\\b" << "\\bnull\\b";

    }
    else if ( iLangType == 3 ) { // C#
        keywordPatterns << "\\babstract\\b" << "\\bas\\b" << "\\bbase\\b"
                        << "\\bbool\\b" << "\\bbreak\\b" << "\\bbyte\\b"
                        << "\\bcase\\b" << "\\bcatch\\b" << "\\bchar\\b"
                        << "\\bchecked\\b" << "\\bclass\\b" << "\\bconst\\b"
                        << "\\bcontinue\\b" << "\\bdecimal\\b" << "\\bdefault\\b"
                        << "\\bdelegate\\b" << "\\bdo\\b" << "\\bdouble\\b"
                        << "\\belse\\b" << "\\benum\\b" << "\\bevent\\b"
                        << "\\bexplicit\\b" << "\\bextern\\b" << "\\bfalse\\b"
                        << "\\bfinally\\b" << "\\bfixed\\b" << "\\bfloat\\b"
                        << "\\bfor\\b" << "\\bforeach\\b" << "\\bgoto\\b"
                        << "\\bif\\b" << "\\bimplicit\\b" << "\\bin\\b"
                        << "\\bint\\b" << "\\binterface\\b" << "\\binternal\\b"
                        << "\\bis\\b" << "\\block\\b" << "\\blong\\b"
                        << "\\bnamespace\\b" << "\\bnew\\b" << "\\bnull\\b"
                        << "\\bobject\\b" << "\\boperator\\b" << "\\bout\\b"
                        << "\\boverride\\b" << "\\bparams\\b" << "\\bprivate\\b"
                        << "\\bprotected\\b" << "\\bpublic\\b" << "\\breadonly\\b"
                        << "\\bref\\b" << "\\breturn\\b" << "\\bsbyte\\b"
                        << "\\bsealed\\b" << "\\bshort\\b" << "\\bsizeof\\b"
                        << "\\bstackalloc\\b" << "\\bstatic\\b" << "\\bstring\\b"
                        << "\\bstruct\\b" << "\\bswitch\\b" << "\\bthis\\b"
                        << "\\bthrow\\b" << "\\btrue\\b" << "\\btry\\b"
                        << "\\btypeof\\b" << "\\buint\\b" << "\\bulong\\b"
                        << "\\bunchecked\\b" << "\\bunsafe\\b" << "\\bushort\\b"
                        << "\\busing\\b" << "\\bvirtual\\b" << "\\bvoid\\b"
                        << "\\bvolatile\\b" << "\\bwhile\\b";
    }
    else if ( iLangType == 4 ) { // Go language
        keywordPatterns << "\\bbreak\\b" << "\\bcase\\b" << "\\bchan\\b"
                        << "\\bconst\\b" << "\\bcontinue\\b" << "\\bdefault\\b"
                        << "\\bdefer\\b" << "\\belse\\b" << "\\bfallthrough\\b"
                        << "\\bfor\\b" << "\\bfunc\\b" << "\\bgo\\b"
                        << "\\bgoto\\b" << "\\bif\\b" << "\\bimport\\b"
                        << "\\binterface\\b" << "\\bmap\\b" << "\\bpackage\\b"
                        << "\\brange\\b" << "\\breturn\\b" << "\\bselect\\b"
                        << "\\bstruct\\b" << "\\bswitch\\b" << "\\btype\\b"
                        << "\\bvar\\b" << "\\bbool\\b" << "\\bint\\b"
                        << "\\bstring\\b" << "\\buint8\\b" << "\\buint16\\b"
                        << "\\buint32\\b" << "\\buint64\\b" << "\\bint8\\b"
                        << "\\bint16\\b" << "\\bint32\\b" << "\\bint64\\b"
                        << "\\bfloat32\\b" << "\\bfloat64\\b" << "\\bcomplex64\\b"
                        << "\\bcomplex128\\b" << "\\bbyte\\b" << "\\brune\\b"
                        << "\\buint\\b" << "\\buintptr\\b" << "\\blen\\b"
                        << "\\btrue\\b" << "\\bfalse\\b" << "\\bnil\\b";

    }
    else if ( iLangType == 5 ) { // Java Script
        keywordPatterns << "\\babstract\\b" << "\\barguments\\b" << "\\bboolean\\b"
                        << "\\bbreak\\b" << "\\bbyte\\b" << "\\bcase\\b"
                        << "\\bcatch\\b" << "\\bchar\\b" << "\\bclass\\b"
                        << "\\bconst\\b" << "\\bcontinue\\b" << "\\bdebugger\\b"
                        << "\\bdefault\\b" << "\\bdelete\\b" << "\\bdo\\b"
                        << "\\bdouble\\b" << "\\belse\\b" << "\\benum\\b"
                        << "\\beval\\b" << "\\bexport\\b" << "\\bextends\\b"
                        << "\\bfalse\\b" << "\\bfinal\\b" << "\\bfinally\\b"
                        << "\\bfloat\\b" << "\\bfor\\b" << "\\bfunction\\b"
                        << "\\bgoto\\b" << "\\bif\\b" << "\\bimplements\\b"
                        << "\\bimport\\b" << "\\bin\\b" << "\\binstanceof\\b"
                        << "\\bint\\b" << "\\binterface\\b" << "\\blet\\b"
                        << "\\blong\\b" << "\\bnative\\b" << "\\bnew\\b"
                        << "\\bnull\\b" << "\\bpackage\\b" << "\\bprivate\\b"
                        << "\\bprotected\\b" << "\\bpublic\\b" << "\\breturn\\b"
                        << "\\bshort\\b" << "\\bstatic\\b" << "\\bsuper\\b"
                        << "\\bswitch\\b" << "\\bsynchronized\\b" << "\\bthis\\b"
                        << "\\bthrow\\b" << "\\bthrows\\b" << "\\btransient\\b"
                        << "\\btrue\\b" << "\\btry\\b" << "\\btypeof\\b"
                        << "\\bvar\\b" << "\\bvoid\\b" << "\\bvolatile\\b"
                        << "\\bwhile\\b" << "\\bwith\\b" << "\\byield\\b";
    }
    else if ( iLangType == 6 ) { // PHP
        keywordPatterns << "\\babstract\\b" << "\\band\\b" << "\\barray\\b" << "\\bcase\\b"
                        << "\\bas\\b" << "\\bbreak\\b" << "\\bclass\\b" << "\\bconst\\b"
                        << "\\bcontinue\\b" << "\\bdeclare\\b" << "\\bdefault\\b"
                        << "\\bdo\\b" << "\\belse\\b" << "\\belseif\\b"  << "\\bnull\\b"
                        << "\\benddeclare\\b" << "\\bendfor\\b" << "\\bendforeach\\b"
                        << "\\bendif\\b" << "\\bendswitch\\b" << "\\bendwhile\\b"
                        << "\\bextends\\b" << "\\bfinal\\b" << "\\bfor\\b"
                        << "\\bforeach\\b" << "\\bfunction\\b" << "\\bglobal\\b"
                        << "\\bgoto\\b" << "\\bif\\b" << "\\bimplements\\b"
                        << "\\binterface\\b" << "\\binstanceof\\b" << "\\bnamespace\\b"
                        << "\\bnew\\b" << "\\bold_function\\b" << "\\bor\\b"
                        << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                        << "\\bstatic\\b" << "\\bswitch\\b" << "\\bthrow\\b"
                        << "\\btry\\b" << "\\buse\\b" << "\\bvar\\b"
                        << "\\bwhile\\b" << "\\bxor\\b" << "\\b__CLASS__\\b"
                        << "\\b__DIR__\\b" << "\\b__FILE__\\b" << "\\b__FUNCTION__\\b"
                        << "\\b__METHOD__\\b" << "\\b__NAMESPACE__\\b" << "\\bdie\\b"
                        << "\\becho\\b" << "\\bempty\\b" << "\\bexit\\b"
                        << "\\beval\\b" << "\\binclude\\b" << "\\binclude_once\\b"
                        << "\\bisset\\b" << "\\blist\\b" << "\\brequire\\b"
                        << "\\brequire_once\\b" << "\\breturn\\b" << "\\bprint\\b"
                        << "\\bunset\\b" << "\\bphp\\b" << "\\bcatch\\b" << "\\bclone\\b"
                        << "\\bself\\b" << "\\btrue\\b" << "\\bfalse\\b" << "\\bthis\\b"
                        << "\\bfinally\\b" << "\\bparent\\b" << "\\btrait\\b";
    }
    else if ( iLangType == 7 ) { // HTML
        keywordPatterns << "\\bDOCTYPE\\b";
    }
    else if ( iLangType == 8 ) { // TEXT
        keywordPatterns << "\\b(0)\\b" << "\\b(1)\\b" << "\\b(2)\\b"
                        << "\\b(3)\\b" << "\\b(4)\\b" << "\\b(5)\\b"
                        << "\\b(6)\\b" << "\\b(7)\\b" << "\\b(8)\\b"
                        << "\\b(9)\\b" << "\\b(10)\\b" << "\\b0)\\b"
                        << "\\b1)\\b" << "\\b2)\\b" << "\\b3)\\b"
                        << "\\b4)\\b" << "\\b5)\\b" << "\\b6)\\b"
                        << "\\b7)\\b" << "\\b8)\\b" << "\\b9)\\b"
                        << "\\b10)\\b";
    }
    else if ( iLangType == 9 ) { // SQL
        keywordPatterns << "\\b(INSERT|insert)\\b" << "\\b(UPDATE|update)\\b" << "\\b(DELETE|delete)\\b"
                        << "\\b(SELECT|select)\\b" << "\\b(WHERE|where)\\b" << "\\b(SET|set)\\b"
                        << "\\b(AND|and)\\b" << "\\b(OR|or)\\b" << "\\b(ORDER|order)\\b"
                        << "\\b(BY|by)\\b" << "\\b(GROUP|group)\\b" << "\\b(HAVING|having)\\b"
                        << "\\b(CREATE|create)\\b" << "\\b(TABLE|table)\\b" << "\\b(FROM|from)\\b"
                        << "\\b(INTO|into)\\b" << "\\b(JOIN|join)\\b" << "\\b(INNER|inner)\\b"
                        << "\\b(OUTTER|outter)\\b" << "\\b(RIGHT|right)\\b" << "\\b(SELF|self)\\b"
                        << "\\b(PRIMARY|primary)\\b" << "\\b(KEY|key)\\b" << "\\b(FOREIGN|foreign)\\b"
                        << "\\b(AS|as)\\b" << "\\b(CONSTRAINT|constraint)\\b" << "\\b(IN|in)\\b"
                        << "\\b(VALUES|values)\\b" << "\\b(NULL|null)\\b" << "\\b(NOT|not)\\b"
                        << "\\b(LIKE|like)\\b" << "\\b(DROP|drop)\\b" << "\\b(REFERENCES|references)\\b"
                        << "\\b(DEFAULT|default)\\b" << "\\b(VIEW|view)\\b" << "\\b(USE|use)\\b"
                        << "\\b(GO|go)\\b" << "\\b(UNION|union)\\b" << "\\b(ALL|all)\\b"
                        << "\\b(BETWEEN|between)\\b" << "\\b(INDEX|index)\\b" << "\\b(UNIQUE|unique)\\b"
                        << "\\b(ON|on)\\b" << "\\b(BEGIN|begin)\\b" << "\\b(END|end)\\b"
                        << "\\b(IF|if)\\b" << "\\b(ELSE|else)\\b" << "\\b(WHILE|while)\\b"
                        << "\\b(BREAK|break)\\b" << "\\b(CONTINUE|continue)\\b" << "\\b(RETURN|return)\\b"
                        << "\\b(TO|to)\\b" << "\\b(WAITFOR|waitfor)\\b" << "\\b(CASE|case)\\b"
                        << "\\b(RAISERROR|raiserror)\\b" << "\\b(DECLARE|declare)\\b" << "\\b(WHEN|when)\\b"
                        << "\\b(THEN|then)\\b" << "\\b(ALTER|alter)\\b" << "\\b(OPEN|open)\\b"
                        << "\\b(FETCH|fetch)\\b" << "\\b(CLOSE|close)\\b" << "\\b(DEALLOCATE|deallocate)\\b"
                        << "\\b(DISTINCT|distinct)\\b" << "\\b(SHOW|show)\\b" << "\\b(DESC|desc)\\b"
                        << "\\b(ASC|asc)\\b" << "\\b(TRUNCATE|truncate)\\b" << "\\b(LIMIT|limit)\\b"
                        << "\\b(LEFT|left)\\b";
    }
    else if ( iLangType == 10 ) { // Python
        keywordPatterns << "\\band\\b" << "\\bdel\\b" << "\\bfrom\\b"
                        << "\\bnot\\b" << "\\bwhile\\b" << "\\bas\\b"
                        << "\\belif\\b" << "\\bglobal\\b" << "\\bor\\b"
                        << "\\bwith\\b" << "\\bassert\\b" << "\\belse\\b"
                        << "\\bif\\b" << "\\bpass\\b" << "\\byield\\b"
                        << "\\bbreak\\b" << "\\bexcept\\b" << "\\bimport\\b"
                        << "\\bprint\\b" << "\\bclass\\b" << "\\bexec\\b"
                        << "\\bin\\b" << "\\braise\\b" << "\\bcontinue\\b"
                        << "\\bfinally\\b" << "\\bis\\b" << "\\breturn\\b"
                        << "\\bdef\\b" << "\\bfor\\b" << "\\blambda\\b"
                        << "\\btry\\b" << "\\balias\\b" << "\\bbegin\\b"
                        << "\\bcase\\b" << "\\bdefined?\\b" << "\\bdo\\b"
                        << "\\belsif\\b" << "\\bend\\b" << "\\bensure\\b"
                        << "\\bfalse\\b" << "\\bmodule\\b" << "\\bnext\\b"
                        << "\\bnil\\b" << "\\bredo\\b" << "\\brescue\\b"
                        << "\\bretry\\b" << "\\bself\\b" << "\\bsuper\\b"
                        << "\\bthen\\b" << "\\btrue\\b" << "\\bundef\\b"
                        << "\\bunless\\b" << "\\buntil\\b" << "\\bwhen\\b";
    }
    else if ( iLangType == 11 ) { // Ruby
        keywordPatterns << "\\bBEGIN\\b" << "\\bEND\\b" << "\\b__ENCODING__\\b"
                        << "\\b__END__\\b" << "\\b__FILE__\\b" << "\\b__LINE__\\b"
                        << "\\balias\\b" << "\\band\\b" << "\\bbegin\\b"
                        << "\\bbreak\\b" << "\\bcase\\b" << "\\bclass\\b"
                        << "\\bdef\\b" << "\\bdefined?\\b" << "\\bdo\\b"
                        << "\\belse\\b" << "\\belsif\\b" << "\\bend\\b"
                        << "\\bensure\\b" << "\\bfalse\\b" << "\\bfor\\b"
                        << "\\bif\\b" << "\\bin\\b" << "\\bmodule\\b"
                        << "\\bnext\\b" << "\\bnil\\b" << "\\bnot\\b"
                        << "\\bor\\b" << "\\bredo\\b" << "\\brescue\\b"
                        << "\\bretry\\b" << "\\breturn\\b" << "\\bself\\b"
                        << "\\bsuper\\b" << "\\bthen\\b" << "\\btrue\\b"
                        << "\\bundef\\b" << "\\bunless\\b" << "\\buntil\\b"
                        << "\\bwhen\\b" << "\\bwhile\\b" << "\\byield\\b";
    }

    foreach ( const QString &pattern, keywordPatterns ) {
        rule.pattern = QRegExp( pattern );
        rule.format = _keywordFormat;

        _highlightingRules.append( rule );
    }

    //classFormat.setFontWeight(QFont::Bold);
    _classFormat.setForeground( QBrush(QColor(0, 153, 230)) );
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = _classFormat;
    _highlightingRules.append( rule );


    _multiLineCommentFormat.setForeground( Qt::darkGreen );

    _doubleQuotationFormat.setForeground( QBrush(QColor(122, 31, 92)) );
    rule.pattern = QRegExp("\".*\"");
    rule.format = _doubleQuotationFormat;
    _highlightingRules.append( rule );

    _singleQuotationFormat.setForeground( QBrush(QColor(255, 71, 26)) );
    rule.pattern = QRegExp("'.*'");
    rule.format = _singleQuotationFormat;
    _highlightingRules.append( rule );

    //functionFormat.setFontItalic(true);
    _functionFormat.setForeground( Qt::darkRed );
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = _functionFormat;
    _highlightingRules.append( rule );

    //-----------------------------------------------------
    // # 주석
    //singleLineMacroFormat.setFontWeight(QFont::Bold);
    _singleLineMacroFormat.setForeground(  Qt::darkBlue );
    rule.pattern = QRegExp( "#[^\n]*" );
    rule.format = _singleLineMacroFormat;
    _highlightingRules.append(rule);

    //-----------------------------------------------------
    // //로 사용하는 line comment
    _singleLineCommentFormat.setForeground( Qt::darkGreen );
    rule.pattern = QRegExp( "//[^\n]*" );
    rule.format = _singleLineCommentFormat;
    _highlightingRules.append( rule );

    if ( iLangType == 7 ) { // HTML
        _tagFormat.setForeground( QBrush(QColor(0, 128, 0)) );
        //_tagFormat.setFontWeight( QFont::Bold );
        rule.pattern = QRegExp("(<[\\w:]+\\b|<\\?[\\w:]+\\b|\\?>|<!|>|/>|</[a-zA-Z:]+>)");
        rule.format = _tagFormat;
        _highlightingRules.append( rule );

        _attributeFormat.setForeground(Qt::red);
        rule.pattern = QRegExp("[a-zA-Z:]+=");
        rule.format = _attributeFormat;
        _highlightingRules.append( rule );
    }
    else if ( iLangType == 8 ) { // TEXT
        _tagFormat.setForeground(Qt::darkBlue);
        _tagFormat.setFontWeight(QFont::Bold);
        rule.pattern = QRegExp("(<[\\w\\s:]+\\b|<\\?[\\w:]+\\b|\\?>|>|/>|</[a-zA-Z:]+>)");
        rule.format = _tagFormat;
        _highlightingRules.append( rule );
    }


    //if ( iLangType == 10 ) {
    //    _commentStartExpression = QRegExp("/\"");
    //    _commentEndExpression = QRegExp("\"/");
    //}
    //else {
        _commentStartExpression = QRegExp("/\\*");
        _commentEndExpression = QRegExp("\\*/");
    //}
}

void Highlighter::highlightBlock( const QString &strText ) {
    foreach ( const HighlightingRule &rule, _highlightingRules ) {
        QRegExp expression( rule.pattern );
        int index = expression.indexIn( strText );
        while ( index >= 0 ) {
            int length = expression.matchedLength();
            setFormat( index, length, rule.format );
            index = expression.indexIn( strText, index + length );
        }
    }
    setCurrentBlockState( 0 );


    //-------------------------------------------------------------------
    int iStartIndex = 0;
    if ( previousBlockState() != 1 )
        iStartIndex = _commentStartExpression.indexIn( strText );

    while ( iStartIndex >= 0 ) {

        int iEndIndex = _commentEndExpression.indexIn( strText, iStartIndex );
        int iCommentLength = 0;
        if ( iEndIndex == -1 ) {
            setCurrentBlockState( 1 );
            iCommentLength = strText.length() - iStartIndex;
        }
        else {
            iCommentLength = iEndIndex - iStartIndex + _commentEndExpression.matchedLength();
        }

        setFormat( iStartIndex, iCommentLength, _multiLineCommentFormat );
        iStartIndex = _commentStartExpression.indexIn( strText, iStartIndex + iCommentLength );
    }
}

