/*
 * Site: restbed.corvusoft.co.uk
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * Restbed is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Restbed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Restbed.  If not, see <http://www.gnu.org/licenses/>.
 */

//System Includes
#include <cstdarg>

//Project Includes
#include "restbed/detail/helpers/string.h"

//External Includes

//System Namespaces
using std::string;
using std::vector;

//Project Namespaces

//External Namespaces

namespace restbed
{
	namespace detail
	{
		namespace helpers
		{
		    const char* String::empty = "";

	        string String::lowercase( const string& value )
	        {
	            string result = empty;
	            
	            transform( value.begin( ), value.end( ), back_inserter( result ), (int (*)(int))tolower );
	            
	            return result;
	        }
	        
	        string String::uppercase( const string& value )
	        {
	            string result = empty;
	            
	            transform( value.begin( ), value.end( ), back_inserter( result ), (int (*)(int))toupper );
	            
	            return result;
	        }

	        string String::join( const string& format, ... )
			{
			    va_list arguments;

			    va_start( arguments, format );

			    string::size_type size = format.size( ) * 2;

			    char* formatted = new char[ size ];

			    int written = vsprintf( formatted, format.data( ), arguments );

			    while ( written < 0 )
			    {
			       delete[ ] formatted;

			       size *= 2;

			       formatted = new char[ size ];

			       written = vsprintf( formatted, format.data( ), arguments );
			    }

			    va_end( arguments );

			    string result = formatted;

			    delete[ ] formatted;

			    return result;
			}

			string String::deduplicate( const string& value, const char target )
			{
			    string result = String::empty;

			    stringstream stream( value );

			    for ( int index = 0; index not_eq value.length( ); index++ )
			    {       
			        char character = stream.get( );

			        if ( character == target )
			        {
			            char next_character = stream.peek( );

			            if ( next_character not_eq target )
			            {
			                result.push_back( character );
			            }
			        }
			        else
			        {
			            result.push_back( character );
			        }
			    }

			    return result;
			}

	        vector< string > String::split(const string& value, const char delimiter )
	        {
	            vector< string > tokens;
	            
	            string::size_type start = 0;
	            string::size_type end = 0;
	            
	            while ( ( end = value.find( delimiter, start ) ) not_eq string::npos )
	            {
	                string text = value.substr( start, end - start );
	                
	                if ( not text.empty( ) )
	                {
	                    tokens.push_back( text );
	                }
	                
	                start = end + 1;
	            }
	            
	            string token = value.substr( start );
	            
	            if ( not token.empty( ) and token not_eq value )
	            {
	                tokens.push_back( token );
	            }
	            
	            return tokens;
	        }

	        string String::trim( const string& value, const string& delimiter )
	        {
	            string result = empty;

	            result = trim_leading( value, delimiter );

	            result = trim_lagging( result, delimiter );

	            return result;
	        }

	        string String::trim_leading( const string& value, const string& delimiter )
	        {
	            string result = value;

	            size_t position = result.find_first_not_of( delimiter );

	            if( string::npos not_eq position )
	            {
	                result = result.substr( position );
	            }

	            return result;
	        }

	        string String::trim_lagging( const string& value, const string& delimiter )
	        {
	            string result = value;

	            size_t position = result.find_last_not_of( delimiter );

	            if( string::npos not_eq position )
	            {
	                result = result.substr( 0, position + 1 );
	            }

	            return result;
	        }

	        string String::remove( const string& needle, const string& haystack, bool case_insensitive )
	        {
	            string target = case_insensitive ? String::lowercase( needle ) : needle;
	            string source = case_insensitive ? String::lowercase( haystack ) : haystack;

	            string::size_type index = source.find( target );

	            if ( index not_eq string::npos )
	            {
	                source.replace( index, target.length( ), empty );
	            }

	            return source;
	        }
		}
	}
}