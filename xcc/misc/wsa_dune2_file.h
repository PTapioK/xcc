// wsa_dune2_file.h: interface for the Cwsa_dune2_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WSA_DUNE2_FILE_H__4AE5F9E0_704F_11D4_B606_0000B4936994__INCLUDED_)
#define AFX_WSA_DUNE2_FILE_H__4AE5F9E0_704F_11D4_B606_0000B4936994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cc_file_sh.h"
#include "cc_structures.h"
#include "fname.h"
#include "palet.h"
#include "video_file.h"
#include "virtual_image.h"

class Cwsa_dune2_file: public Cvideo_file<t_wsa_dune2_header>  
{
public:
	void decode(void* d) const;
	int extract_as_pcx(const Cfname& name, t_file_type ft, const t_palet _palet) const;
	bool is_valid() const;
	Cvirtual_image vimage() const;

	int cb_pixel() const
	{
		return 1;
	}

	int cf() const
	{
		return get_header()->c_frames;
	}

	int cx() const
	{
		return get_header()->cx;
	}

	int cy() const
	{
		return get_header()->cy;
	}

	/*
	int get_delta() const
	{
		return get_header()->delta;
	}
	*/

	const byte* get_frame(int i) const
	{
		return get_data() + get_offset(i);
	}

	int get_cb_ofs() const
	{
		return get_index16()[1] ? 2 : 4;
	}

	int get_ofs(int i) const
	{
		if (get_cb_ofs() == 2)
			return get_index16()[i];
		else
			return get_index32()[i];
	}

	int get_cb_delta() const
	{
		return *reinterpret_cast<const __int16*>(get_data() + sizeof(t_wsa_dune2_header)) ? 2 : 4;
	}

	const __int16* get_index16() const
	{
		return reinterpret_cast<const __int16*>(get_data() + sizeof(t_wsa_dune2_header) + get_cb_delta() - 2);
	}

	const __int32* get_index32() const
	{
		return reinterpret_cast<const __int32*>(get_data() + sizeof(t_wsa_dune2_header) + get_cb_delta() - 2);
	}

    int get_offset(int i) const
    {
		return get_ofs(i);
    }

	bool has_loop() const
	{
		return get_ofs(cf() + 1);
	}
};

#endif // !defined(AFX_WSA_DUNE2_FILE_H__4AE5F9E0_704F_11D4_B606_0000B4936994__INCLUDED_)
