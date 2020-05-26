@page pageReqs Requirements

[TOC]
<!-- @tableofcontents  -->

<!-- @section Introduction -->

# Scope

# Definitions

- **Term**:
- **Score**:
- **Dictionary**:

# Problem Statement
Calculate score of the sentence based on the dictionary.


# Deliverables
 - [ ] readme
 - [ ] development solution description
 - [ ] build system to compile the code
 - [ ] source code and tests
 - [x] logging level
 - [ ] search for term first

# Overview of Solution

//TODO 

<!-- # Use cases -->

<!-- @section requirements Description of Requirements -->


# Terms Dictionary

## Terms Dictionary Structure
@anchor TS_REQ-TD_Structure
Contains terms. 
Terms are unique.
Terms can be stop-words. 
Terms in the dictionary have scores.


## Terms Language
@anchor TS_REQ-TD_DictLang
Term dictionary contains English terms.

## Dictionary Case
@anchor TS_REQ-TD_Case
Not case sensitive.

## Dictionary Size
@anchor TS_REQ-TD_Size
Minimum size of dictionary – 100000 words/terms.

## Single-Word Terms
@anchor TS_REQ-TD_SingleWordTerms
Terms can be single word - desktop, keyboard, world, apple, etc

## Multiple-Word Terms
@anchor TS_REQ-TD_MultiWordTerms
Terms can be combination of words – hello world, New York, Apple Computers, etc.


# Stop-words
@anchor TS_REQ-SW_List
List of stop-words is given.

# Sentence
## Sentence Size
@anchor TS_REQ-SNTNC_Size
Max number of terms in a sentence – 500.

## Sentence Case
@anchor TS_REQ-SNTNC_Case
Not case sensitive.

# Scores
## Score of a Term
@anchor TS_REQ-SCR_ScoreMatrix
Score is represented in 10x10 binary matrix.

## Score of a Sentence
@anchor TS_REQ-SCR_SentenceScore
Score of the sentence is a matrix constructed as binary sum of the 
score matrices from terms in a sentence.
Return 10x10 0 filled matrix if neither of the terms exists in the dictionary. 

## Skip Missing Terms
@anchor TS_REQ-SCR_MissingTerms
Skip the term missing in the dictionary.

## Skip Stop-words
@anchor TS_REQ-SCR_StopWords
Skip the stop words in the sentence during the score calculation.

# User Interface
## Command Line Arguments
@anchor TS_REQ-UI_CLI
User provides flags and argument values to run the
program. User can get help via `--help` flag.
## Command Line Dictionary Setting
@anchor TS_REQ-UI_CLDictSetting
## Command Line Stop-words Setting
@anchor TS_REQ-UI_CLStopWordsSetting
## Sentence Input
@anchor TS_REQ-UI_SentenceInput
User enters the sentence to be scored.
## Logging
@anchor TS_REQ-UI_Logging
When enabled, log per specified logging level. 
## Command Line Logging Setting
@anchor TS_REQ-UI_CLLoggingSetting


# Implementation Requirements
## Term Lookup Implementation
@anchor TS_REQ-Impl_TermLookup
Terms both in dictionary and sentence shall be represented 
as 64 bit integers (hash methodology).
## Implementation Language
@anchor TS_REQ-Impl_Lang
The implementation should be done with C++98 standard. 



