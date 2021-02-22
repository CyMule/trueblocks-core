/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2018, 2019 TrueBlocks, LLC (http://trueblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
/*
 * This file was generated with makeClass. Edit only those parts of the code inside
 * of 'EXISTING_CODE' tags.
 */
#include "entitycache.h"

namespace qblocks {

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CEntityCache, CCache);

//---------------------------------------------------------------------------
static string_q nextEntitycacheChunk(const string_q& fieldIn, const void* dataPtr);
static string_q nextEntitycacheChunk_custom(const string_q& fieldIn, const void* dataPtr);

//---------------------------------------------------------------------------
void CEntityCache::Format(ostream& ctx, const string_q& fmtIn, void* dataPtr) const {
    if (!m_showing)
        return;

    // EXISTING_CODE
    // EXISTING_CODE

    string_q fmt = (fmtIn.empty() ? expContext().fmtMap["entitycache_fmt"] : fmtIn);
    if (fmt.empty()) {
        if (expContext().exportFmt == YAML1) {
            toYaml(ctx);
        } else {
            toJson(ctx);
        }
        return;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    while (!fmt.empty())
        ctx << getNextChunk(fmt, nextEntitycacheChunk, this);
}

//---------------------------------------------------------------------------
string_q nextEntitycacheChunk(const string_q& fieldIn, const void* dataPtr) {
    if (dataPtr)
        return reinterpret_cast<const CEntityCache*>(dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------
string_q CEntityCache::getValueByName(const string_q& fieldName) const {
    // Give customized code a chance to override first
    string_q ret = nextEntitycacheChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // EXISTING_CODE
    // EXISTING_CODE

    // Return field values
    switch (tolower(fieldName[0])) {
        case 'i':
            if (fieldName % "items" || fieldName % "itemsCnt") {
                size_t cnt = items.size();
                if (endsWith(toLower(fieldName), "cnt"))
                    return uint_2_Str(cnt);
                if (!cnt)
                    return "";
                string_q retS;
                for (size_t i = 0; i < cnt; i++) {
                    retS += items[i].Format();
                    retS += ((i < cnt - 1) ? ",\n" : "\n");
                }
                return retS;
            }
            break;
        default:
            break;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CCache::getValueByName(fieldName);
}

//---------------------------------------------------------------------------------------------------
bool CEntityCache::setValueByName(const string_q& fieldNameIn, const string_q& fieldValueIn) {
    string_q fieldName = fieldNameIn;
    string_q fieldValue = fieldValueIn;

    // EXISTING_CODE
    // EXISTING_CODE

    if (CCache::setValueByName(fieldName, fieldValue))
        return true;

    switch (tolower(fieldName[0])) {
        case 'i':
            if (fieldName % "items") {
                CEntityCacheItem obj;
                string_q str = fieldValue;
                while (obj.parseJson3(str)) {
                    items.push_back(obj);
                    obj = CEntityCacheItem();  // reset
                }
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void CEntityCache::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CEntityCache::Serialize(CArchive& archive) {
    if (archive.isWriting())
        return SerializeC(archive);

    // Always read the base class (it will handle its own backLevels if any, then
    // read this object's back level (if any) or the current version.
    CCache::Serialize(archive);
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> items;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CEntityCache::SerializeC(CArchive& archive) const {
    // Writing always write the latest version of the data
    CCache::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << items;

    return true;
}

//---------------------------------------------------------------------------
CArchive& operator>>(CArchive& archive, CEntityCacheArray& array) {
    uint64_t count;
    archive >> count;
    array.resize(count);
    for (size_t i = 0; i < count; i++) {
        ASSERT(i < array.capacity());
        array.at(i).Serialize(archive);
    }
    return archive;
}

//---------------------------------------------------------------------------
CArchive& operator<<(CArchive& archive, const CEntityCacheArray& array) {
    uint64_t count = array.size();
    archive << count;
    for (size_t i = 0; i < array.size(); i++)
        array[i].SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
void CEntityCache::registerClass(void) {
    // only do this once
    if (HAS_FIELD(CEntityCache, "schema"))
        return;

    CCache::registerClass();

    size_t fieldNum = 1000;
    ADD_FIELD(CEntityCache, "schema", T_NUMBER, ++fieldNum);
    ADD_FIELD(CEntityCache, "deleted", T_BOOL, ++fieldNum);
    ADD_FIELD(CEntityCache, "showing", T_BOOL, ++fieldNum);
    ADD_FIELD(CEntityCache, "cname", T_TEXT, ++fieldNum);
    ADD_FIELD(CEntityCache, "items", T_OBJECT | TS_ARRAY | TS_OMITEMPTY, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CEntityCache, "schema");
    HIDE_FIELD(CEntityCache, "deleted");
    HIDE_FIELD(CEntityCache, "showing");
    HIDE_FIELD(CEntityCache, "cname");

    builtIns.push_back(_biCEntityCache);

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextEntitycacheChunk_custom(const string_q& fieldIn, const void* dataPtr) {
    const CEntityCache* ent = reinterpret_cast<const CEntityCache*>(dataPtr);
    if (ent) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if (fieldIn % "parsed")
                    return nextBasenodeChunk(fieldIn, ent);
                // EXISTING_CODE
                // EXISTING_CODE
                break;

            default:
                break;
        }
    }

    return "";
}

//---------------------------------------------------------------------------
bool CEntityCache::readBackLevel(CArchive& archive) {
    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const CEntityCache& it) {
    // EXISTING_CODE
    // EXISTING_CODE

    it.Format(os, "", nullptr);
    os << "\n";
    return os;
}

//---------------------------------------------------------------------------
const CBaseNode* CEntityCache::getObjectAt(const string_q& fieldName, size_t index) const {
    if (fieldName % "items") {
        if (index == NOPOS) {
            CEntityCacheItem empty;
            ((CEntityCache*)this)->items.push_back(empty);  // NOLINT
            index = items.size() - 1;
        }
        if (index < items.size())
            return &items[index];
    }

    return NULL;
}

//---------------------------------------------------------------------------
const char* STR_DISPLAY_ENTITYCACHE = "";

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE
}  // namespace qblocks
