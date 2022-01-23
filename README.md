# Page Rank Matrix

### Table Of Contents
- [Table Of Contents](#table-of-contents)
- [Installation](#instalation)
- [About](#about)

### Installation

Simulate Google Page Rank algorithm using matrix.

To run the project and make changes to the project clone the repository. Then, reload the CMakeLists.txt for the IDE to recompile the .idea and cmake-build-debug folders.

### About

Take a couple of minutes to understand what this program does, and how the algorithm is implemented:

1 Let W be a set of webpages (a web) of size n.

2 Let G be a square connectivity matrix. A connectivity matrix is a square matrix of 0s and 1s used to represent the connections in a graph (or web). If there is a hyperlink from page j to page i, there is a 1 at location [i][j]. If there is no link from page j to page i, then there is a 0 at location [i][j].

3 Suppose we have a tiny web W of 4 pages: A, B, C, and D, and apart from page D which has no links to it or from it, each page contains one link to each of the other pages, but not to itself. That is, page A contains a link to page B, and to page C, but not to page A or to page D. Page B contains a link to page A, and to page C, but not to page B or page D. And so on. We say that the jth column of the connectivity matrix contains the outbound links from page j. Our connectivity matrix will look like this:

G =  

| | a | b | c |  d |
|-----------|:-----------:|:-----------:|:-----------:|-----------:|    
| a | 0 | 1 | 1 | 0 |
| b | 1 | 0 | 1 | 0 |
| c | 1 | 1 | 0 | 0 |
| d | 0 | 0 | 0 | 0 |

4 Let’s define the importance of each page by the importance of the pages that link to it.  (Hey wait, that sounds a little like recursion!). If we do this, we can use the connectivity matrix as a starting point for determining the relative importance of each page in our web. Note that a typical connectivity matrix G is probably very big (how many billions (trillions) of web pages are there these days), but very sparse (lots of zeros). Its jth column shows the links on the jth page, and the total number of nonzero entries in the entire matrix is the total number of links in our web W.

5 We can define ri and cj to be the row and column sums of G respectively. These quantities are the in-degree and out-degree. The in-degree is the number of pages that have links to our ith page, and the out-degree is the number of links on our jth page to other pages.

6 Take a break and this about this. This is neat. There’s a lot of math in search engines, and there’s some pretty interesting vocabulary involved. We’re using matrices. We’re using a special kind of matrix called a con- nectivity matrix which is all zeros and ones. The matrix can be sparse, and has row and column sums. The sum of 1s in a row is the in-degree because it is a count of the links to the page at row i. The sum of 1s in a column is the out-degree because it is the number of links out from the page at column j.

7 We can modify our connectivity matrix to show us this “importance” if we divide each value in each column by the sum of each column. Since it is a connectivity matrix, the values in the cells are either 0 or 1, so each cell containing a 1 is divided by the number of 1s in the column. For example, in our connectivity matrix G, the sum in the first column (column A) is 2, so we divide each element by 2 to get 0.5. We can observe that every non- zero column now adds up to 1. Let S be the matrix constructed according to this rule:

S = 

| | a | b | c |  d |
|-----------|:-----------:|:-----------:|:-----------:|-----------:|    
| a | 0 | 0.5 | 0.5 | 0 |
| b | 0.5 | 0 | 0.5 | 0 |
| c | 0.5 | 0.5 | 0 | 0 |
| d | 0 | 0 | 0 | 0 |

8 In matrix S, the value in S[i][j] is the ”probability” of going from page j to page i. Note that every non-zero column adds up to 1, but we have that pesky final column of zeros to worry about. There are no links to page D, and there are no links away from page D. We have to do something about this, otherwise page D is going to end up at the bottom of the PageRank no matter how interesting its contents. We want to replace every column of zeros with a column whose elements equal 1/n (recall n is the dimension of our square connectivity matrix):

S = 

| | a | b | c |  d |
|-----------|:-----------:|:-----------:|:-----------:|-----------:|    
| a | 0 | 0.5 | 0.5 | 0.25 |
| b | 0.5 | 0 | 0.5 | 0.25 |
| c | 0.5 | 0.5 | 0 | 0.25 |
| d | 0 | 0 | 0 | 0.25 |

9 Are you still with us? Good! The matrix S is now a stochastic matrix, or to be more specific, a left stochastic matrix because the columns all sum to 1. In a left stochastic matrix, the elements are all strictly between 0 and 1 and its columns all sum to 1. We’re almost finished. We can also call S a probability matrix, and we will use our probability matrix to construct a transition matrix for a Markov process. This sounds much more complicated than it really is. There are two steps:

10 We need to introduce the notion of a random walk. We need to multiply our probability matrix by a random walk probability factor. For our lab, we will designate this variable p, and set p = 0.85.

11 The next step is the most complicated step (and it’s not complicated at all). We need to add (1 - p) multiplied by a matrix Q, whose every element = 1 / n. (recall that a rank 1 matrix has a single linearly independent column). Let’s call the transition matrix that results M. Use the formula:

    M = 0.85 * S + (1 - 0.85) * Q

12 Now comes the fun part, the “dynamical system” portion of our algorithm. Start with a matrix of size n x 1, a column matrix of 1s called rank:

rank =


| 1 |
|-----------|
| 1 |
| 1 |
| 1 |

13 The final 2 steps are the Markov process (aka the dynamical system aka the power method):

14 Multiply the transition matrix M by our column matrix rank, and then multiply M by the result and then keep doing this until the rank stops changing (result converges), e.g., M * rank = rank. In this case, we get:

rank = 

| 1.2698 |
|-----------|
| 1.2698 |
| 1.2698 |
| 0.1905 |

15 Finally (last step!) divide each element in rank by the sum of the values in rank (scale rank so its elements sum to 1):

rank = 

| 0.3175 |
|-----------|
| 0.3175 |
| 0.3175 |
| 0.0476 |

