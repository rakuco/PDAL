/******************************************************************************
* Copyright (c) 2012, Michael P. Gerlek (mpg@flaxen.com)
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following
* conditions are met:
*
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in
*       the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of Hobu, Inc. or Flaxen Consulting LLC nor the
*       names of its contributors may be used to endorse or promote
*       products derived from this software without specific prior
*       written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
****************************************************************************/

#pragma once

#include <pdal/Options.hpp>
#include <pdal/pdal_internal.hpp>
#include <pdal/util/ProgramArgs.hpp>

#include <vector>

#ifdef PDAL_COMPILER_GCC
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wredundant-decls"
#  pragma GCC diagnostic ignored "-Wextra"
#  pragma GCC diagnostic ignored "-Wcast-qual"
   // The following pragma doesn't actually work:
   //   https://gcc.gnu.org/bugzilla/show_bug.cgi?id=61653
   //#  pragma GCC diagnostic ignored "-Wliteral-suffix"
#endif
#ifdef PDAL_COMPILER_CLANG
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#define IMPORT_NITRO_API
#include <nitro/c++/import/nitf.hpp>

#ifdef PDAL_COMPILER_CLANG
#  pragma clang diagnostic pop
#endif
#ifdef PDAL_COMPILER_GCC
#  pragma GCC diagnostic pop
#endif

namespace pdal
{
    class MetadataNode;
}


namespace pdal
{

//
// all the processing that is NITF-file specific goes in here
//
class PDAL_DLL NitfFile
{
public:
    NitfFile();
    NitfFile(const std::string& filename);

    void openExisting();
    void setFilename(const std::string& filename)
        { m_filename = filename; }
    void getLasOffset(uint64_t& offset, uint64_t& length);
    void extractMetadata(MetadataNode& metadata);
    void wrapData(const char *buf, size_t size);
    void wrapData(const std::string& filename);
    void setArgs(ProgramArgs& args);
    void setBounds(const BOX3D& bounds);
    void processOptions(const Options& options);
    void write();

private:
    bool locateLidarImageSegment();
    bool locateLidarDataSegment();

    std::unique_ptr<nitf::DataSource> m_source;
    std::unique_ptr<nitf::IOHandle> m_io;
    std::unique_ptr<nitf::IOHandle> m_inputHandle;
    nitf::Record m_record;

    std::string m_cLevel;
    std::string m_sType;
    std::string m_oStationId;
    std::string m_fileTitle;
    std::string m_fileClass;
    std::string m_origName;
    std::string m_origPhone;
    std::string m_securityClass;
    std::string m_securityControlAndHandling;
    std::string m_securityClassificationSystem;
    std::string m_imgSecurityClass;
    std::string m_imgDate;
    StringList m_aimidb;
    StringList m_acftb;
    std::string m_imgIdentifier2;
    std::string m_sic;
    BOX3D m_bounds;

    std::string m_filename;
    bool m_validLidarSegments;
    ::nitf::Uint32 m_lidarImageSegment;
    ::nitf::Uint32 m_lidarDataSegment;

    NitfFile(const NitfFile&); // nope
    NitfFile& operator=(const NitfFile&); // nope
};


} // namespaces
