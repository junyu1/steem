#pragma once

#include <mira/multi_index_container.hpp>
#include <mira/ordered_index.hpp>
#include <mira/tag.hpp>
#include <mira/member.hpp>
#include <mira/indexed_by.hpp>
#include <mira/composite_key.hpp>
#include <mira/mem_fun.hpp>

#include <fc/reflect/reflect.hpp>

struct book : public chainbase::object< 0, book > {

   template<typename Constructor, typename Allocator>
   book(  Constructor&& c, Allocator&& a )
   {
      c(*this);
   }

   book() = default;

   id_type id;
   int a = 0;
   int b = 1;

   int sum()const { return a + b; }
};

struct by_id;
struct by_a;
struct by_b;
struct by_sum;

typedef mira::multi_index_container<
   book,
   mira::multi_index::indexed_by<
      mira::multi_index::ordered_unique< mira::multi_index::tag< by_id >, mira::multi_index::member< book, book::id_type, &book::id > >,
      mira::multi_index::ordered_unique< mira::multi_index::tag< by_a >,  mira::multi_index::member< book, int,           &book::a  > >,
      mira::multi_index::ordered_unique< mira::multi_index::tag< by_b >,
         mira::multi_index::composite_key< book,
            mira::multi_index::member< book, int, &book::b >,
            mira::multi_index::member< book, int, &book::a >
         >,
         mira::multi_index::composite_key_compare< std::greater< int >, std::less< int > >
      >,
      mira::multi_index::ordered_unique< mira::multi_index::tag< by_sum >, mira::multi_index::const_mem_fun< book, int, &book::sum > >
  >,
  chainbase::allocator< book >
> book_index;

struct single_index_object : public chainbase::object< 1, single_index_object >
{
   template< typename Constructor, typename Allocator >
   single_index_object( Constructor&& c, Allocator&& a )
   {
      c( *this );
   }

   single_index_object() = default;

   id_type id;
};

typedef mira::multi_index_container<
   single_index_object,
   mira::multi_index::indexed_by<
      mira::multi_index::ordered_unique< mira::multi_index::tag< by_id >, mira::multi_index::member< single_index_object, single_index_object::id_type, &single_index_object::id > >
   >,
   chainbase::allocator< single_index_object >
> single_index_index;

struct test_object : public chainbase::object< 2, test_object >
{
   template <class Constructor, class Allocator>
   test_object(Constructor&& c, Allocator a ) : id( 0 ), val( 0 ), name( a )
   {
      c(*this);
   }

   template <class Constructor, class Allocator>
   test_object(Constructor&& c, int64_t _id, Allocator a ) : id( _id ), val( 0 ), name( a )
   {
      c(*this);
   }

   id_type id;
   uint32_t val;
   std::string name;
};

struct OrderedIndex;
struct CompositeOrderedIndex;

typedef mira::multi_index_container<
   test_object,
   mira::multi_index::indexed_by<
      mira::multi_index::ordered_unique< mira::multi_index::tag< OrderedIndex >, mira::multi_index::member< test_object, chainbase::oid< test_object >, &test_object::id > >,
      mira::multi_index::ordered_unique< mira::multi_index::tag< CompositeOrderedIndex >,
         mira::multi_index::composite_key< test_object,
            mira::multi_index::member< test_object, std::string, &test_object::name >,
            mira::multi_index::member< test_object, uint32_t, &test_object::val >
         >
      >
   >,
   chainbase::allocator< test_object >
> test_object_index;

struct test_object2 : public chainbase::object< 3, test_object2 >
{
   template <class Constructor, class Allocator>
   test_object2(Constructor&& c, Allocator a ) : id( 0 ), val( 0 )
   {
      c(*this);
   }

   id_type id;
   uint32_t val;
};

struct OrderedIndex2;
struct CompositeOrderedIndex2;

typedef mira::multi_index_container<
   test_object2,
   mira::multi_index::indexed_by<
      mira::multi_index::ordered_unique< mira::multi_index::tag< OrderedIndex2 >, mira::multi_index::member< test_object2, chainbase::oid< test_object2 >, &test_object2::id > >,
      mira::multi_index::ordered_unique< mira::multi_index::tag< CompositeOrderedIndex2 >,
         mira::multi_index::composite_key< test_object2,
            mira::multi_index::member< test_object2, uint32_t, &test_object2::val >,
            mira::multi_index::member< test_object2, chainbase::oid<test_object2>, &test_object2::id >
         >
      >
   >,
   chainbase::allocator< test_object2 >
> test_object2_index;

struct test_object3 : public chainbase::object< 3, test_object3 >
{
   template <class Constructor, class Allocator>
   test_object3(Constructor&& c, Allocator a ) : id( 0 ), val( 0 ), val2( 0 ), val3( 0 )
   {
      c(*this);
   }

   id_type id;
   uint32_t val;
   uint32_t val2;
   uint32_t val3;
};

struct OrderedIndex3;
struct CompositeOrderedIndex3a;
struct CompositeOrderedIndex3b;

typedef mira::multi_index_container<
   test_object3,
   mira::multi_index::indexed_by<
      mira::multi_index::ordered_unique< mira::multi_index::tag< OrderedIndex3 >, mira::multi_index::member< test_object3, chainbase::oid< test_object3 >, &test_object3::id > >,
      mira::multi_index::ordered_unique< mira::multi_index::tag< CompositeOrderedIndex3a>,
         mira::multi_index::composite_key< test_object3,
            mira::multi_index::member< test_object3, uint32_t, &test_object3::val >,
            mira::multi_index::member< test_object3, uint32_t, &test_object3::val2 >
         >
      >,
      mira::multi_index::ordered_unique< mira::multi_index::tag< CompositeOrderedIndex3b>,
         mira::multi_index::composite_key< test_object3,
            mira::multi_index::member< test_object3, uint32_t, &test_object3::val >,
            mira::multi_index::member< test_object3, uint32_t, &test_object3::val3 >
         >
      >
   >,
   chainbase::allocator< test_object3 >
> test_object3_index;

FC_REFLECT( book::id_type, (_id) )
FC_REFLECT( book, (id)(a)(b) )
CHAINBASE_SET_INDEX_TYPE( book, book_index )

FC_REFLECT( single_index_object::id_type, (_id) )
FC_REFLECT( single_index_object, (id) )
CHAINBASE_SET_INDEX_TYPE( single_index_object, single_index_index )

FC_REFLECT( test_object::id_type, (_id) )
FC_REFLECT( test_object, (id)(val)(name) )
CHAINBASE_SET_INDEX_TYPE( test_object, test_object_index )

FC_REFLECT( test_object2::id_type, (_id) )
FC_REFLECT( test_object2, (id)(val) )
CHAINBASE_SET_INDEX_TYPE( test_object2, test_object2_index )

FC_REFLECT( test_object3::id_type, (_id) )
FC_REFLECT( test_object3, (id)(val)(val2)(val3) )
CHAINBASE_SET_INDEX_TYPE( test_object3, test_object3_index )