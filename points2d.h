// Zachary Motassim

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_
#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
 public:


  // Zero-parameter constructor.
  // Set size to 0.
  Points2D() { // just having things set to their default values, no need for heap allocation
  size_ = 0 ;
  sequence_ = nullptr ;
  }

  // Copy-constructor.
  Points2D(const Points2D &rhs) {
    size_ = rhs.size_ ;
    sequence_ = new std::array<Object, 2> [ size_ ] ;
    for ( size_t i = 0 ; i < size_ ; ++i ) {
      sequence_[ i ] = rhs.sequence_[ i ] ;
    }

  }

  Points2D& operator=( const Points2D &rhs ) { // pass an instance
    Points2D copy = rhs; //create another instance set equal to first instance
    std::swap( *this, copy ) ; // swap the instances
    return *this;
  }
  // Move-constructor.
  Points2D( Points2D &&rhs ) {
    // set equal, then set to default
    size_ = rhs.size_;
    rhs.size_ = 0;
			sequence_ = rhs.sequence_ ;
      //delete rhs.sequence_ ;
			rhs.sequence_ = nullptr ;
  } // takes the velues given

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2D& operator=( Points2D &&rhs ) {
    std::swap( size_ , rhs.size_ ) ;
    std::swap( sequence_ , rhs.sequence_ ) ;
    return *this ;
  }

  ~Points2D( ){
    delete [] sequence_ ;
    sequence_ = nullptr ;
  }

  // End of big-five.

  // One parameter constructor.
  Points2D(const std::array<Object, 2>& item) {
    // Provide code.
    size_ = 1 ;
    sequence_ = new std::array<Object, 2>( item ) ;
  }

  // Read a chain from standard input.
  void ReadPoints2D() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line);
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;
    // Allocate space for sequence.
    // Add code here.
    size_ = size_of_sequence ;
    sequence_ = new std::array< Object , 2 > [ size_ ] ;
    Object token;
    for (int i = 0 ;input_stream >> token; ++i) {
      // Read coordinates.
      // Fill sequence_ here.
      sequence_[ i ][ 0 ] = token ;
      input_stream >> token ;
      sequence_[ i ][ 1 ] = token ;
    }
    std::cout << std::endl ;

  }

  size_t size() const { return size_ ; }
  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const {
    //if ( location > sequence_.size_ ){ std::abort( ) ; }
    if ( location > size_ ){ std::abort( ) ; }
    return sequence_[ location ] ;
  }


 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their difference. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
 friend Points2D operator-(const Points2D &c1, const Points2D &c2) {
   Points2D sequence_sum ;
   if(c1.size_ >c2.size_){
     sequence_sum.size_ = c1.size_ ;
   }
   else{
     sequence_sum.size_ = c2.size_ ;
   }
   sequence_sum.sequence_ = new std::array<Object, 2> [ sequence_sum.size_ ] ; //[ sequence_sum.size_ ] ;
   for( size_t i = 0 ; i < sequence_sum.size_ ; ++i ){
   sequence_sum.sequence_[ i ][ 0 ] = c1[ i ][ 0 ] - c2[ i ][ 0 ] ;
   sequence_sum.sequence_[ i ][ 1 ] = c1[ i ][ 1 ] - c2[ i ][ 1 ] ;
  }
  return sequence_sum;
}

//concatenates two sequences
friend Points2D operator+( const Points2D &c1, const Points2D &c2 ) {
  Points2D Concatenated ;
  Concatenated.size_ = c1.size_ + c2.size_ ;
  Concatenated.sequence_ = new std::array<Object, 2> [ Concatenated.size_ ] ;
  for( size_t i = 0 ; i < c1.size_ ; ++i ){
    Concatenated.sequence_[ i ][ 0 ] = c1[ i ][ 0 ] ;
    Concatenated.sequence_[ i ][ 1 ] = c1[ i ][ 1 ] ;
  }
  size_t j = 0 ;
  for(size_t i =  c1.size_  ; i < Concatenated.size_ ; ++i ){
    Concatenated.sequence_[ i ][ 0 ] = c2[ j ][ 0 ] ; ;
    Concatenated.sequence_[ i ][ 1 ] = c2[ j ][ 1 ] ;
    j++ ;
  }
  return Concatenated ;
}

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2) {
   if( some_points2.size_ == 0){ out<< "()" ; }
   for (size_t i = 0 ; i < some_points2.size_ ; ++i ) {
     out << "(" << some_points2.sequence_[ i ][ 0 ] << ", " << some_points2.sequence_[ i ][ 1 ] << ")" << " " ;
   }
   return out << std::endl ;
 }

 private:
  // Sequence of points.
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_                    ;

};

}
#endif
